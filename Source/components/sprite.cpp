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
}

SpriteComponent::~SpriteComponent( )
{
}

void SpriteComponent::Draw( sf::RenderTarget& target )
{
	PositionComponent* posComp = PositionComponent::Get( m_owner );
	if( posComp )
	{
		m_sprite.setPosition( posComp->GetPosition() );
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
