#pragma once

#include <set>
#include <map>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <functional>
#include "vector2Comparator.hpp"
#include "colorConversion.hpp"

class TriggerComponent;
class MovableComponent;
class CollisionMapComponent;

class Physics
{
public:
	Physics();
	~Physics();

	void RegisterTrigger( TriggerComponent& trigger );
	void UnregisterTrigger( TriggerComponent& trigger );
	void RegisterMovable( MovableComponent& movable );
	void UnregisterMovable( MovableComponent& movable );
	void RegisterCollisionMap( CollisionMapComponent& collisionMap );
	void UnregisterCollisionMap( CollisionMapComponent& collisionMap );

	bool OnFloor( const sf::IntRect& rect ) const;

private:
	Physics( const Physics& ) = delete;
	Physics( Physics&& ) = delete;
	Physics& operator=( const Physics& ) = delete;

	PixelType GetPixelType( int x, int y ) const;
	void Update( const sf::Time& delta );

	typedef std::set< TriggerComponent* > TriggerSet;
	typedef std::set< MovableComponent* > MovableSet;
	typedef std::map< sf::Vector2i, CollisionMapComponent*, Vector2iComparator > CollisionMapMap;

	TriggerSet m_triggers;
	MovableSet m_movables;
	CollisionMapMap m_collisionMaps;
	sf::Vector2u m_tileSize;
	std::function< void( const sf::Time& ) > m_frameCallback;
};