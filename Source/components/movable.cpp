#include "movable.hpp"
#include "position.hpp"
#include "rect.hpp"
#include "../physics.hpp"

#include <cassert>
#include <stdexcept>

MovableComponent::MovableComponent( Entity& owner, Physics& physics )
: Component( owner )
, m_physics( physics )
{
	m_physics.RegisterMovable( *this );
}

MovableComponent::~MovableComponent()
{
	m_physics.UnregisterMovable( *this );
}

void MovableComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
	m_rect = RectComponent::Get( m_owner );
	if( !m_position )
	{
		throw std::logic_error( "MovableComponent used without PositionComponent!" );
	}
	if( !m_rect )
	{
		throw std::logic_error( "MovableComponent used without RectComponent!" );
	}
}

const std::string& MovableComponent::GetType() const
{
	static const std::string type( "movable" );
	return type;
}

MovableComponent* MovableComponent::Get( const Entity& entity )
{
	return dynamic_cast< MovableComponent* >( GetComponent( entity, "movable" ) );
}

sf::IntRect MovableComponent::GetGlobalRect() const
{
	assert( m_rect );
	return m_rect->GetGlobalRect();
}

sf::Vector2i MovableComponent::GetPosition() const
{
	assert( m_position );
	return m_position->GetPosition();
}