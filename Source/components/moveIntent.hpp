#pragma once

#include <SFML/System/Vector2.hpp>

#include "../component.hpp"

namespace sf
{
	class Time;
}

class GameplaySettings;

class MoveIntentComponent : public Component
{
public: 
	struct Parameters
	{
	};

	MoveIntentComponent( Entity& owner, Parameters&& parameters );
	~MoveIntentComponent() = default;

	const std::string& GetType() const;

	static std::shared_ptr< MoveIntentComponent > Get( const Entity& entity );

	sf::Vector2i Apply( const sf::Vector2i& velocity, const sf::Time& delta );

private:
	const Parameters m_parameters;
};
