#pragma once

#include "../entity.hpp"

#include <memory>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Texture;
class SpriteGroup;
struct GameplaySettings;
class Physics;
class PositionComponent;
class MoveIntentComponent;

class Player : public Entity
{
public:
	Player( sf::Vector2i&& position, const sf::IntRect& rect, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics, const GameplaySettings& settings, std::function< void() > onPlayerKilled );
	~Player() = default;
	Player( const Player& ) = delete;
	Player( Player&& ) = delete;
	Player& operator=( const Player& ) = delete;

	const sf::Vector2i& GetPosition() const;

private:
	std::shared_ptr< PositionComponent > m_position;
	std::shared_ptr< MoveIntentComponent > m_moveIntent;
};
