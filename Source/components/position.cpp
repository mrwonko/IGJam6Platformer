#include "position.hpp"
#include <utility>

PositionComponent::PositionComponent( Entity& owner, int x, int y )
: Component( owner )
, m_position( x, y )
{
}

PositionComponent::PositionComponent( Entity& owner, sf::Vector2i&& position )
: Component( owner )
, m_position( std::move( position ) )
{
}

PositionComponent::~PositionComponent()
{
}


std::shared_ptr< PositionComponent > PositionComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< PositionComponent >( GetComponent( entity, "position" ) );
}

const std::string& PositionComponent::GetType() const
{
	static std::string type( "position" );
	return type;
}
