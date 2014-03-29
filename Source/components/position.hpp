#pragma once

#include "../component.hpp"

#include <SFML/System/Vector2.hpp>

class PositionComponent : public Component
{
public:
	static std::shared_ptr< PositionComponent > Get( const Entity& entity );

	PositionComponent( Entity& owner, int x, int y );
	PositionComponent( Entity& owner, sf::Vector2i&& position );
	~PositionComponent();

	const std::string& GetType() const;

	const sf::Vector2i& GetPosition() const { return m_position;  }
	sf::Vector2i& GetPosition() { return m_position; }

private:
	sf::Vector2i m_position;
};
