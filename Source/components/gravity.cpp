#include "gravity.hpp"
#include <SFML/System/Time.hpp>
#include <cmath>

GravityComponent::GravityComponent( Entity& owner, unsigned int gravity )
: Component( owner )
, m_gravity( gravity )
{
}

const std::string& GravityComponent::GetType() const
{
	static const std::string type( "gravity" );
	return type;
}

std::shared_ptr< GravityComponent > GravityComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< GravityComponent >( GetComponent( entity, "gravity" ) );
}

sf::Vector2i GravityComponent::Apply( const sf::Vector2i& velocity, const sf::Time& delta )
{
	return sf::Vector2i(
		velocity.x,
		velocity.y + int( std::round( m_gravity * delta.asSeconds() ) )
		);
}
