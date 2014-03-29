#pragma once

#include "../entity.hpp"

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Texture;
class SpriteGroup;
class GameplaySettings;
class Physics;

class Player : public Entity
{
public:
	Player( sf::Vector2i&& position, const sf::IntRect& rect, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics, const GameplaySettings& settings );
	~Player() = default;
	Player( const Player& ) = delete;
	Player( Player&& ) = delete;
	Player& operator=( const Player& ) = delete;
};
