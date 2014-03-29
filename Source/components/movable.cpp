#include "movable.hpp"
#include "position.hpp"
#include "rect.hpp"
#include "gravity.hpp"
#include "moveIntent.hpp"
#include "../physics.hpp"
#include "../debug.hpp"

#include <cassert>

MovableComponent::MovableComponent( Entity& owner, Physics& physics, const sf::Vector2i& velocity )
: Component( owner )
, m_physics( physics )
, m_velocity( velocity )
{
}

MovableComponent::~MovableComponent()
{
	m_physics.UnregisterMovable( *this );
}

void MovableComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
	m_rect = RectComponent::Get( m_owner );
	m_gravity = GravityComponent::Get( m_owner );
	m_moveIntent = MoveIntentComponent::Get( m_owner );
	if( !m_position )
	{
		Debug::Error( "MovableComponent used without PositionComponent!" );
	}
	if( !m_rect )
	{
		Debug::Error( "MovableComponent used without RectComponent!" );
	}
	m_physics.RegisterMovable( *this );
}

const std::string& MovableComponent::GetType() const
{
	static const std::string type( "movable" );
	return type;
}

std::shared_ptr< MovableComponent > MovableComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< MovableComponent >( GetComponent( entity, "movable" ) );
}

sf::IntRect MovableComponent::GetGlobalRect() const
{
	assert( m_rect );
	return m_rect->GetGlobalRect();
}

const sf::Vector2i& MovableComponent::GetPosition() const
{
	assert( m_position );
	return m_position->GetPosition();
}

sf::Vector2i& MovableComponent::GetPosition()
{
	assert( m_position );
	return m_position->GetPosition();
}

bool MovableComponent::OnFloor() const
{
	return m_physics.OnFloor( GetGlobalRect() );
}

void MovableComponent::Update( const sf::Time& delta )
{
	if( m_gravity )
	{
		m_velocity = m_gravity->Apply( m_velocity, delta );
	}
	if( m_moveIntent )
	{
		m_velocity = m_moveIntent->Apply( m_velocity, delta );
	}
}
