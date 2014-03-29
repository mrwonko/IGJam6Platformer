#pragma once

#include "../component.hpp"

#include <SFML/System/Vector2.hpp>

class PositionComponent : public Component
{
public:
	static PositionComponent* Get( const Entity& entity );

	PositionComponent( Entity& owner, float x, float y );
	PositionComponent( Entity& owner, sf::Vector2f&& position );
	~PositionComponent();

	const std::string& GetType() const;

	const sf::Vector2f& GetPosition() const { return m_position;  }
	sf::Vector2f& GetPosition() { return m_position; }

private:
	sf::Vector2f m_position;
};
