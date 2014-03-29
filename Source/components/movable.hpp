#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "../component.hpp"

class PositionComponent;
class Physics;
class RectComponent;
class MoveIntentComponent;
class GravityComponent;

namespace sf
{
	class Time;
}

class MovableComponent : public Component
{
	// calls Update() and may change velocity.
	friend class Physics;

public:
	MovableComponent( Entity& owner, Physics& physics, const sf::Vector2i& velocity = sf::Vector2i( 0, 0 ) );
	~MovableComponent();

	const std::string& GetType( ) const;

	static std::shared_ptr< MovableComponent > Get( const Entity& entity );

	void Init();

	sf::IntRect GetGlobalRect() const;
	const sf::Vector2i& GetPosition() const;
	sf::Vector2i& GetPosition();

	const sf::Vector2i& GetVelocity() const { return m_velocity; }

	bool OnFloor() const;

private:
	Physics& m_physics;
	std::shared_ptr< PositionComponent > m_position;
	std::shared_ptr< RectComponent > m_rect;
	std::shared_ptr< GravityComponent > m_gravity;
	std::shared_ptr< MoveIntentComponent > m_moveIntent;
	sf::Vector2i m_velocity;

	void Update( const sf::Time& delta );
	sf::Vector2i& GetVelocity() { return m_velocity; }
};
