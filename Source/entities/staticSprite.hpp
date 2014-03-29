#pragma once

#include "../entity.hpp"

#include <SFML/System/Vector2.hpp>
#include <memory>

class SpriteGroup;
class Texture;

class StaticSprite : public Entity
{
public:
	StaticSprite( sf::Vector2i&& position, std::shared_ptr< const Texture > texture, SpriteGroup& group );
	~StaticSprite() = default;
	StaticSprite( const StaticSprite& ) = delete;
	StaticSprite( StaticSprite&& ) = delete;
	StaticSprite& operator=( const StaticSprite& ) = delete;
};
