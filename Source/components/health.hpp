#pragma once

#include "../component.hpp"

#include <functional>

class HealthComponent : public Component
{
public:
	HealthComponent( Entity& owner, int health );
	~HealthComponent( ) = default;

	/// Callback parameter: Damage taken
	void SetDamageCallback( std::function< void( int ) > damageCallback )
	{
		m_onDamageCallback = damageCallback; 
	}

	void SetKillCallback( std::function< void() > killCallback )
	{
		m_onKillCallback = killCallback;
	}

	const std::string& GetType() const;

	static std::shared_ptr< HealthComponent > Get( const Entity& entity );

	void Damage( int damage );

	void Kill();

	const int GetHealth() const { return m_health; }

	bool IsDead() const { return m_health <= 0; }

private:
	int m_health;

	std::function< void( int ) > m_onDamageCallback;
	std::function< void() > m_onKillCallback;
};
