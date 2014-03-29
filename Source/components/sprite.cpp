#include "sprite.hpp"
#include "position.hpp"
#include "../entity.hpp"
#include "../texture.hpp"
#include "../spriteGroup.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

SpriteComponent::SpriteComponent( Entity& owner, std::shared_ptr< const Texture > texture, SpriteGroup& group )
: Component( owner )
, m_sprite( texture->GetTexture() )
, m_texture( texture )
, m_group( group )
{
	// TODO: Animations (register frame callback)
}

SpriteComponent::~SpriteComponent( )
{
	m_group.UnregisterSprite( *this );
	// TODO: Animations (unregister frame callback)
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
