#include "staticSprite.hpp"

#include "../components/position.hpp"
#include "../components/sprite.hpp"

StaticSprite::StaticSprite( sf::Vector2i&& position, std::shared_ptr< const Texture > texture, SpriteGroup& group )
{
	AddComponent( std::make_shared< PositionComponent >( *this, std::move( position ) ) );
	AddComponent( std::make_shared< SpriteComponent >( *this, texture, group ) );
	InitComponents();
}
