#pragma once

#include <memory>
#include <string>

#include <SFML/System/Vector2.hpp>

#include "../entity.hpp"

class Texture;
class TextureManager;
class Physics;
class SpriteGroup;

namespace sf
{
	class Image;
}

class Tile : public Entity
{
public:
	typedef std::unique_ptr< Tile > Ptr;

	/**
		Levelpath without trailing slash, e.g. "../data/level_willi"
		Extension is assumed to be .png

		@return nullptr if the level image can't be loaded.
		@throw std::runtime_error if the collision map can't be loaded.
	**/
	static Ptr LoadTile( const std::string& levelpath, sf::Vector2i&& position, SpriteGroup& group, Physics& physics, TextureManager& textureManager );

private:
	Tile( sf::Vector2i&& position, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics, const sf::Image& collisionMap );

	Tile( const Tile& ) = delete;
	Tile( Tile&& ) = delete;
	Tile& operator=( const Tile& ) = delete;
};
