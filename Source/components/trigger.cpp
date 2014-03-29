#include "trigger.hpp"
#include "rect.hpp"
#include "../physics.hpp"

#include <cassert>
#include <stdexcept>

TriggerComponent::TriggerComponent( Entity& owner, Physics& physics, const Callback& onEnter )
: Component( owner )
, m_physics( physics )
, m_onEnter( onEnter )
, m_rect( nullptr )
{
	m_physics.RegisterTrigger( *this );
}

TriggerComponent::~TriggerComponent()
{
	m_physics.UnregisterTrigger( *this );
}

void TriggerComponent::Init()
{
	m_rect = RectComponent::Get( m_owner );
	if( !m_rect )
	{
		throw std::logic_error( "TriggerComponent used without RectComponent!" );
	}
}

std::shared_ptr< TriggerComponent > TriggerComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< TriggerComponent >( GetComponent( entity, "trigger" ) );
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
	assert( m_rect );
	return m_rect->GetGlobalRect();
}
