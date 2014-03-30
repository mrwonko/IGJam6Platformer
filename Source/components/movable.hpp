#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>

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

	const std::string& GetType() const;

	static std::shared_ptr< MovableComponent > Get( const Entity& entity );

	/// Defines callback for movable-movable collisions
	void SetCollideCallback( std::function< void( Entity& ) > callback )
	{
		m_onCollideCallback = callback;
	}

	void Init();

	void SetMaxStep( int maxStep ) { m_maxStep = maxStep;  }

	sf::IntRect GetGlobalRect() const;
	const sf::Vector2i& GetPosition() const;
	sf::Vector2i& GetPosition();

	const sf::Vector2i& GetVelocity() const { return m_velocity; }
	sf::Vector2i& GetVelocity() { return m_velocity; }

	bool OnFloor() const;

	/// Movable-Movable collisions
	void OnCollide( Entity& other ) const;

private:
	void Update( const sf::Time& delta );

	Physics& m_physics;
	std::shared_ptr< PositionComponent > m_position;
	std::shared_ptr< RectComponent > m_rect;
	std::shared_ptr< GravityComponent > m_gravity;
	std::shared_ptr< MoveIntentComponent > m_moveIntent;
	sf::Vector2i m_velocity;
	std::function< void( Entity& ) > m_onCollideCallback;
	int m_maxStep{ 0 };
};
