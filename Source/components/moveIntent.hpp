#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "../component.hpp"

namespace sf
{
	class Time;
}

class MovableComponent;
struct GameplaySettings;

class MoveIntentComponent : public Component
{
public: 
	struct Parameters
	{
		int moveSpeed;
		int jumpImpulse;
		int acceleration;
	};

	struct Intent
	{
		bool right{ false };
		bool left{ false };
		bool jump{ false };
	};

	MoveIntentComponent( Entity& owner, Parameters&& parameters );
	~MoveIntentComponent() = default;

	void Init();

	const std::string& GetType() const;

	static std::shared_ptr< MoveIntentComponent > Get( const Entity& entity );

	/// May also change the animation, if this is a sprite and still alive / has no health
	void SetIntent( const Intent& intent );

	/// May also change the animation, if this is a sprite and still alive / has no health
	sf::Vector2i Apply( const sf::Vector2i& velocity, const sf::Time& delta );

private:
	bool OnFloor() const;

	void StateChanged();

	const Parameters m_parameters;
	Intent m_intent;
	std::weak_ptr< MovableComponent > m_movable;
	bool m_wasOnFloor{ true };
};
