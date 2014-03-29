#pragma once

#include <memory>
#include <set>
#include <functional>

class Entity;

namespace sf
{
	class Time;
}

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	EntityManager( const EntityManager& ) = delete;
	EntityManager( EntityManager&& ) = delete;
	EntityManager& operator= ( const EntityManager& ) = delete;

	void AddEntity( std::unique_ptr< Entity >&& entity );
private:
	/// Drops entities marked for deletion
	void Frame();

	std::set < std::unique_ptr< Entity > > m_entities;
	std::function< void( const sf::Time& ) > m_frameCallback;
};