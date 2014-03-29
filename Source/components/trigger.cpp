#include "trigger.hpp"
#include "position.hpp"
#include "../physics.hpp"

#include <utility>

TriggerComponent::TriggerComponent( Entity& owner, Physics& physics, const sf::IntRect& rect, const Callback& onEnter )
: Component( owner )
, m_physics( physics )
, m_onEnter( onEnter )
, m_rect( rect )
{
	m_physics.RegisterTrigger( *this );
}

TriggerComponent::~TriggerComponent()
{
	m_physics.UnregisterTrigger( *this );
}

void TriggerComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
}

TriggerComponent* TriggerComponent::Get( const Entity& entity )
{
	return dynamic_cast< TriggerComponent* >( GetComponent( entity, "trigger" ) );
}

const std::string& TriggerComponent::GetType() const
{
	static const std::string type( "trigger" );
	return type;
}

void TriggerComponent::OnEnter( Entity& other ) const
{
	m_onEnter( other );
}

sf::IntRect TriggerComponent::GetGlobalRect() const
{
	sf::IntRect rect = m_rect;
	if( m_position )
	{
		rect.left += m_position->GetPosition().x;
		rect.top += m_position->GetPosition().y;
	}
	return rect;
}
