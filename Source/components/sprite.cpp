#include "sprite.hpp"
#include "position.hpp"
#include "../entity.hpp"
#include "../spriteGroup.hpp"
#include "../time.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>

SpriteComponent::SpriteComponent( Entity& owner, std::shared_ptr< const Texture > texture, SpriteGroup& group )
: Component( owner )
, m_sprite( texture->GetTexture() )
, m_texture( texture )
, m_group( group )
, m_animationTimerCallback( [ this ]( const sf::Time& delta ){ UpdateAnimation( delta ); } )
{
	SetAnimation( "idle" );
	Time::RegisterCallback( m_animationTimerCallback );
}

SpriteComponent::~SpriteComponent( )
{
	m_group.UnregisterSprite( *this );
	Time::UnregisterCallback( m_animationTimerCallback );
}

void SpriteComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
	m_group.RegisterSprite( *this );
}

void SpriteComponent::Draw( sf::RenderTarget& target )
{
	if( m_position )
	{
		m_sprite.setPosition(
			float( m_position->GetPosition().x ),
			float( m_position->GetPosition().y )
			);
	}
	// TODO: Animations
	target.draw( m_sprite );
}

std::shared_ptr< SpriteComponent > SpriteComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< SpriteComponent >( GetComponent( entity, "sprite" ) );
}

const std::string& SpriteComponent::GetType( ) const
{
	static std::string type( "sprite" );
	return type;
}


void SpriteComponent::SetAnimation( const std::string& name )
{
	m_curAnimationName = name;
	m_curAnimation = m_texture->GetAnimation( name );
	m_curFrame = m_curAnimation.startFrame;
	m_sprite.setTextureRect( m_texture->GetFrameRect( m_curFrame ) );
}

void SpriteComponent::UpdateAnimation( const sf::Time& delta )
{
	m_frameTime += delta;
	assert( m_curAnimation.frameTime > sf::milliseconds( 0 ) );
	while( m_frameTime >= m_curAnimation.frameTime )
	{
		// On the last frame?
		if( m_curFrame + 1 == m_curAnimation.startFrame + m_curAnimation.length )
		{
			bool justEnded = false;
			if( m_loopAnimation )
			{
				m_curFrame = m_curAnimation.startFrame;
				m_frameTime -= m_curAnimation.frameTime;
				m_sprite.setTextureRect( m_texture->GetFrameRect( m_curFrame ) );
				justEnded = true;
			}
			else
			{
				justEnded = m_frameTime - delta < m_curAnimation.frameTime;
			}
			if( justEnded && m_animationOverCallback )
			{
				m_animationOverCallback( *this );
			}
		}
		else
		{
			++m_curFrame;
			m_frameTime -= m_curAnimation.frameTime;
			m_sprite.setTextureRect( m_texture->GetFrameRect( m_curFrame ) );
		}
	}
}
