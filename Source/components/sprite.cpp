#include "sprite.hpp"
#include "position.hpp"
#include "../entity.hpp"
#include "../texture.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

SpriteComponent::SpriteComponent( Entity& owner, std::shared_ptr< Texture > texture )
: Component( owner )
, m_sprite( texture->GetTexture() )
, m_texture( texture )
{
	// TODO: Animations (register callback)
}

SpriteComponent::~SpriteComponent( )
{
	// TODO: Animations (unregister callback)
}

void SpriteComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
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

SpriteComponent* SpriteComponent::Get( const Entity& entity )
{
	return dynamic_cast< SpriteComponent* >( GetComponent( entity, "sprite" ) );
}

const std::string& SpriteComponent::GetType( ) const
{
	static std::string type( "sprite" );
	return type;
}
