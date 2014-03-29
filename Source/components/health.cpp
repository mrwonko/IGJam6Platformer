#include "health.hpp"

#include <cassert>

HealthComponent::HealthComponent( Entity& owner, int health )
: Component( owner )
, m_health( health )
{
	assert( health > 0 );
}

const std::string& HealthComponent::GetType( ) const
{
	static const std::string type( "health" );
	return type;
}

std::shared_ptr< HealthComponent > HealthComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< HealthComponent >( GetComponent( entity, "health" ) );
}

void HealthComponent::Damage( int damage )
{
	if( m_health <= 0 ) return;

	m_health -= damage;
	if( m_health <= 0 )
	{
		if( m_onKillCallback ) m_onKillCallback();
	}
	else
	{
		if( m_onDamageCallback ) m_onDamageCallback( damage );
	}
}

void HealthComponent::Kill()
{
	if( m_health <= 0 ) return;

	m_health = 0;

	if( m_onKillCallback ) m_onKillCallback( );
}
