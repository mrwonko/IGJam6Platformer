#include "rect.hpp"
#include "position.hpp"

RectComponent::RectComponent( Entity& owner, const sf::IntRect& rect )
: Component( owner )
, m_rect( rect )
{
}

void RectComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
}

sf::IntRect RectComponent::GetGlobalRect() const
{
	sf::IntRect rect = m_rect;
	if( m_position )
	{
		rect.left += int( m_position->GetPosition().x );
		rect.top += int( m_position->GetPosition().y );
	}
	return rect;
}

std::shared_ptr< RectComponent > RectComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< RectComponent >( GetComponent( entity, "rect" ) );
}

const std::string& RectComponent::GetType( ) const
{
	static const std::string type( "rect" );
	return type;
}
