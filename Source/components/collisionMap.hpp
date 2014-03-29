#pragma once

#include "../component.hpp"
#include "../colorConversion.hpp"

#include <SFML/System/Vector2.hpp>
#include <vector>

class Physics;
class PositionComponent;

namespace sf
{
	class Image;
}

/// Binary Solid/Nonsolid values for each pixel
class CollisionMapComponent : public Component
{
public:
	/// Image: White = Nonsolid, Black = Solid
	CollisionMapComponent( Entity& owner, Physics& physics, const sf::Image& image );
	~CollisionMapComponent( );

	const std::string& GetType() const;

	static std::shared_ptr< CollisionMapComponent > Get( const Entity& entity );

	void Init();

	sf::Vector2i GetPosition() const;
	sf::Vector2u GetSize() const { return m_size; }

	PixelType GetPixelType( unsigned int x, unsigned int y ) const;
	PixelType GetPixelType( sf::Vector2u position ) const
	{
		return GetPixelType( position.x, position.y );
	}

private:
	std::vector< bool >::size_type ConvertCoordinate( unsigned int x, unsigned int y ) const
	{
		return y * m_size.x + x;
	}

	Physics& m_physics;
	std::shared_ptr< const PositionComponent > m_position{ nullptr };
	const sf::Vector2u m_size;
	std::vector< PixelType > m_pixmap;
};
