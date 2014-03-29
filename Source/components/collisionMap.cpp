#include "collisionMap.hpp"
#include "position.hpp"
#include "../physics.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

CollisionMapComponent::CollisionMapComponent( Entity& owner, Physics& physics, const sf::Image& image )
: Component( owner )
, m_physics( physics )
, m_size( image.getSize() )
, m_pixmap( m_size.x * m_size.y, false )
{
	// if this is slow consider iterating through image.getAllPixels()
	for( unsigned int y = 0; y < image.getSize().y; ++y )
	{
		for( unsigned int x = 0; x < image.getSize().x; ++x )
		{
			sf::Color pixel( image.getPixel( x, y ) );
			if( unsigned( pixel.r ) + unsigned( pixel.b ) + unsigned( pixel.g ) < 128 * 3 )
			{
				m_pixmap[ ConvertCoordinate( x, y ) ] = true;
			}
		}
	}
	m_physics.RegisterCollisionMap( *this );
}

CollisionMapComponent::~CollisionMapComponent()
{
	m_physics.UnregisterCollisionMap( *this );
}

std::shared_ptr< CollisionMapComponent > CollisionMapComponent::Get( const Entity& entity )
{
	return std::dynamic_pointer_cast< CollisionMapComponent >( GetComponent( entity, "collisionMap" ) );
}

const std::string& CollisionMapComponent::GetType() const
{
	static const std::string type( "collisionMap" );
	return type;
}

void CollisionMapComponent::Init()
{
	m_position = PositionComponent::Get( m_owner );
}

sf::Vector2i CollisionMapComponent::GetPosition() const
{
	if( m_position )
	{
		return sf::Vector2i( int( m_position->GetPosition().x ), int( m_position->GetPosition().y ) );
	}
	else
	{
		return sf::Vector2i( 0, 0 );
	}
}

const bool CollisionMapComponent::IsSolid( unsigned int x, unsigned int y ) const
{
	return m_pixmap.at( ConvertCoordinate( x, y ) );
}
