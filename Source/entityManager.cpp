#include "entityManager.hpp"
#include "time.hpp"
#include "entity.hpp"

EntityManager::EntityManager()
: m_frameCallback( [ this ]( const sf::Time& _ ) { Frame(); } )
{
	Time::RegisterCallback( m_frameCallback );
}

EntityManager::~EntityManager()
{
	Time::UnregisterCallback( m_frameCallback );
}

void EntityManager::AddEntity( std::unique_ptr< Entity >&& entity )
{
	m_entities.emplace( std::move( entity ) );
}

void EntityManager::Frame()
{
	// Delete entities marked for deletion
	for( auto it = m_entities.begin(); it != m_entities.end(); )
	{
		if( ( *it )->MarkedForDeletion() )
		{
			it = m_entities.erase( it );
		}
		else
		{
			++it;
		}
	}
}
