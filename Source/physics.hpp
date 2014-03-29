#pragma once

#include <set>
#include <map>
#include <SFML/System/Vector2.hpp>

class TriggerComponent;
class MovableComponent;
class CollisionMapComponent;

class Physics
{
public:
	void RegisterTrigger( TriggerComponent& trigger );
	void UnregisterTrigger( TriggerComponent& trigger );
	void RegisterMovable( MovableComponent& movable );
	void UnregisterMovable( MovableComponent& movable );
	void RegisterCollisionMap( CollisionMapComponent& collisionMap );
	void UnregisterCollisionMap( CollisionMapComponent& collisionMap );

private:
	bool IsSolid( int x, int y ) const;

	typedef std::set< TriggerComponent* > TriggerSet;
	typedef std::set< MovableComponent* > MovableSet;
	typedef std::map< sf::Vector2i, CollisionMapComponent* > CollisionMapMap;

	TriggerSet m_triggers;
	MovableSet m_movables;
	CollisionMapMap m_collisionMaps;
	sf::Vector2u m_tileSize;
};