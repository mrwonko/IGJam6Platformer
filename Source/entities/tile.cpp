#include "tile.hpp"
#include "../components/position.hpp"
#include "../components/sprite.hpp"
#include "../components/collisionMap.hpp"
#include "../textureManager.hpp"

#include <sstream>

#include <SFML/Graphics/Image.hpp>


Tile::Tile( sf::Vector2i&& position, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics, const sf::Image& collisionMap )
{
	AddComponent( std::make_shared< PositionComponent >( *this, std::move( position ) ) );
	AddComponent( std::make_shared< SpriteComponent >( *this, texture, group ) );
	AddComponent( std::make_shared< CollisionMapComponent >( *this, physics, collisionMap ) );

	InitComponents();
}

Tile::Ptr Tile::LoadTile( const std::string& levelpath, sf::Vector2i&& position, SpriteGroup& group, Physics& physics, TextureManager& textureManager )
{
	std::stringstream filename_base;
	filename_base << levelpath << "/" << position.x << "_" << position.y;
	std::shared_ptr< const Texture > tex = textureManager.Get( filename_base.str() + ".png" );
	if( !tex )
	{
		return nullptr;
	}
	sf::Image collisionMap;
	if( !collisionMap.loadFromFile( filename_base.str() + ".collision.png" ) )
	{
		throw std::runtime_error( "Could not load " + filename_base.str() + ".collision.png!" );
	}
	return Ptr( new Tile( std::move( position ), tex, group, physics, collisionMap ) );
}
