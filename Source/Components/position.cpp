#include "position.hpp"
#include <utility>

PositionComponent::PositionComponent( Entity& owner, float x, float y )
: Component( owner )
, m_position( x, y )
{
}

PositionComponent::PositionComponent( Entity& owner, sf::Vector2f&& position )
: Component( owner )
, m_position( std::move( position ) )
{
}

PositionComponent::~PositionComponent()
{
}


PositionComponent* PositionComponent::Get( const Entity& entity )
{
	return dynamic_cast< PositionComponent* >( GetComponent( entity, "position" ) );
}

const std::string& PositionComponent::GetType() const
{
	static std::string type( "position" );
	return type;
}
