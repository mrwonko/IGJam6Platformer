#include "moveIntent.hpp"
#include "movable.hpp"
#include "position.hpp"
#include <SFML/System/Time.hpp>

#include <iostream>

#include <utility>

MoveIntentComponent::MoveIntentComponent( Entity& owner, Parameters&& parameters )
: Component( owner )
, m_parameters( std::move( parameters ) )
{
}


void MoveIntentComponent::Init()
{
	m_movable = MovableComponent::Get( m_owner );
}

const std::string& MoveIntentComponent::GetType() const
{
	static const std::string type( "moveIntent" );
	return type;
}

std::shared_ptr< MoveIntentComponent > MoveIntentComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< MoveIntentComponent >( GetComponent( entity, "moveIntent" ) );
}

static inline int sign( int i )
{
	return i == 0 ? 0 : ( i > 0 ? 1 : -1 );
}

sf::Vector2i MoveIntentComponent::Apply( const sf::Vector2i& velocity_in, const sf::Time& delta )
{
	sf::Vector2i velocity( velocity_in );

	if( m_intent.jump )
	{
		auto movable = m_movable.lock();
		if( movable && movable->OnFloor() )
		{
			velocity.y = std::min( velocity.y, -m_parameters.jumpImpulse );
		}
	}

	int targetVelocity{ 0 };
	if( m_intent.right )
	{
		targetVelocity += m_parameters.moveSpeed;
	}
	if( m_intent.left )
	{
		targetVelocity -= m_parameters.moveSpeed;
	}

	// If we want to keep the direction, we don't care if we're faster.
	if( sign( targetVelocity ) == sign( velocity.x ) && std::abs( targetVelocity ) < std::abs( velocity.x ) )
	{
		return velocity;
	}

	int difference = targetVelocity - velocity.x;
	if( m_parameters.acceleration == 0 )
	{
		velocity.x += difference;
	}
	else
	{
		int change = sign( difference ) * int( std::round( m_parameters.acceleration * delta.asSeconds() ) );
		if( change > std::abs( difference ) ) change = std::abs( difference );
		if( change < -std::abs( difference ) ) change = -std::abs( difference );

		velocity.x += change;
	}
	return velocity;
}
