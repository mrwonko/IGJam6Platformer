#include "collisionMap.hpp"
#include "position.hpp"
#include "../physics.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

CollisionMapComponent::CollisionMapComponent( Entity& owner, Physics& physics, const sf::Image& image )
: Component( owner )
, m_physics( physics )
, m_size( image.getSize() )
, m_pixmap( m_size.x * m_size.y, PixelType::Air )
{
	// if this is slow consider iterating through image.getAllPixels()
	// profiler says: ignore getPixel, GetMatchingPixelType() is what takes most of the time!
	// TODO: Parallellize this? (Is the overhead worth it? Should Tile-loading be parallellized instead?)
	// Actually, that's just debug checks. Release build loads much faster.
	for( unsigned int y = 0; y < image.getSize().y; ++y )
	{
		for( unsigned int x = 0; x < image.getSize().x; ++x )
		{
			PixelType type = GetMatchingPixelType( image.getPixel( x, y ) );
			if( type != PixelType::Air )
			{
				m_pixmap[ ConvertCoordinate( x, y ) ] = type;
			}
		}
	}
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
	m_physics.RegisterCollisionMap( *this );
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

PixelType CollisionMapComponent::GetPixelType( unsigned int x, unsigned int y ) const
{
	return m_pixmap.at( ConvertCoordinate( x, y ) );
}
