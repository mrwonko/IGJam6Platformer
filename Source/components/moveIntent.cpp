#include "moveIntent.hpp"
#include "movable.hpp"
#include <SFML/System/Time.hpp>

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

sf::Vector2i MoveIntentComponent::Apply( const sf::Vector2i& velocity, const sf::Time& delta )
{
	// TODO: Intent to jump
	if( true )
	{
		auto movable = m_movable.lock();
		if( movable && movable->OnFloor() )
		{
			movable->GetVelocity().y -= m_parameters.jumpImpulse;
		}
	}
	// TODO
	return velocity;
}
