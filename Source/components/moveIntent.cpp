#include "moveIntent.hpp"
#include "movable.hpp"
#include "position.hpp"
#include "sprite.hpp"
#include "health.hpp"
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

static int GetDirection( const MoveIntentComponent::Intent& intent )
{
	int direction = 0;
	if( intent.right ) ++direction;
	if( intent.left ) --direction;
	return direction;
}

void MoveIntentComponent::SetIntent( const Intent& intent )
{
	int prevDirection = GetDirection( m_intent );
	int newDirection = GetDirection( intent );
	m_intent = intent;
	if( prevDirection != newDirection )
	{
		StateChanged();
	}
}

bool MoveIntentComponent::OnFloor() const
{
	auto movable = m_movable.lock();
	return movable && movable->OnFloor();
}

void MoveIntentComponent::StateChanged()
{
	auto sprite = SpriteComponent::Get( m_owner );
	if( !sprite ) return;

	auto health = HealthComponent::Get( m_owner );
	if( health && health->IsDead() ) return;

	int direction = GetDirection( m_intent );
	if( direction < 0 )
	{
		sprite->SetAnimation(
			m_wasOnFloor ? "walkleft" : "jumpleft",
			m_wasOnFloor ? "walk" : "jumpup"
			);
	}
	else if( direction > 0 )
	{
		sprite->SetAnimation(
			m_wasOnFloor ? "walkright" : "jumpright",
			m_wasOnFloor ? "walk" : "jumpup"
			);
	}
	else
	{
		sprite->SetAnimation( m_wasOnFloor ? "idle" : "jumpup" );
	}
}

static inline int sign( int i )
{
	return i == 0 ? 0 : ( i > 0 ? 1 : -1 );
}

sf::Vector2i MoveIntentComponent::Apply( const sf::Vector2i& velocity_in, const sf::Time& delta )
{
	sf::Vector2i velocity( velocity_in );

	if( OnFloor() )
	{
		if( m_intent.jump )
		{
			velocity.y = std::min( velocity.y, -m_parameters.jumpImpulse );
		}
		if( !m_wasOnFloor )
		{
			m_wasOnFloor = true;
			StateChanged();
		}
	}
	else if( m_wasOnFloor )
	{
		m_wasOnFloor = false;
		StateChanged();
	}

	int targetVelocity{ m_parameters.moveSpeed * GetDirection( m_intent ) };

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
