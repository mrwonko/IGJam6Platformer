#pragma once

#include <SFML/System/Vector2.hpp>

#include "../component.hpp"

namespace sf
{
	class Time;
}

class GravityComponent : public Component
{
public:
	GravityComponent( Entity& owner, unsigned int gravity );
	~GravityComponent() = default;

	const std::string& GetType() const;

	static std::shared_ptr< GravityComponent > Get( const Entity& entity );

	sf::Vector2i Apply( const sf::Vector2i& velocity, const sf::Time& delta );

private:
	unsigned int m_gravity;
};
