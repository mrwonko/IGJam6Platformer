#pragma once

#include "../component.hpp"

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
	static CollisionMapComponent * Get( const Entity& entity );

	/// Image: White = Nonsolid, Black = Solid
	CollisionMapComponent( Entity& owner, Physics& physics, const sf::Image& image );
	~CollisionMapComponent( );

	const std::string& GetType() const;

	void Init();

	sf::Vector2i GetPosition() const;
	sf::Vector2u GetSize() const { return m_size; }

	const bool IsSolid( unsigned int x, unsigned int y ) const;
	const bool IsSolid( sf::Vector2u position ) const
	{
		return IsSolid( position.x, position.y );
	}

private:
	std::vector< bool >::size_type ConvertCoordinate( unsigned int x, unsigned int y ) const
	{
		return y * m_size.x + x;
	}

	Physics& m_physics;
	const PositionComponent *m_position{ nullptr };
	const sf::Vector2u m_size;
	std::vector< bool > m_pixmap;
};
