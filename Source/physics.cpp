#include "physics.hpp"
#include "debug.hpp"
#include "time.hpp"
#include "components/collisionMap.hpp"

#include <stdexcept>
#include <cassert>

Physics::Physics()
: m_frameCallback( [ this ]( const sf::Time& delta ) { Update( delta ); } )
{
	Time::RegisterCallback( m_frameCallback );
}

Physics::~Physics()
{
	Time::UnregisterCallback( m_frameCallback );
}

void Physics::RegisterTrigger( TriggerComponent& trigger )
{
	if( !m_triggers.insert( &trigger ).second )
	{
		Debug::Warning( "Duplicate Trigger registration" );
	}
}

void Physics::UnregisterTrigger( TriggerComponent& trigger )
{
	if( m_triggers.erase( &trigger ) == 0 )
	{
		Debug::Warning( "Trying to unregister unregistered Trigger!" );
	}
}

void Physics::RegisterMovable( MovableComponent& movable )
{
	if( !m_movables.insert( &movable ).second )
	{
		Debug::Warning( "Duplicate Movable registration" );
	}
}

void Physics::UnregisterMovable( MovableComponent& movable )
{
	if( m_movables.erase( &movable ) == 0 )
	{
		Debug::Warning( "Trying to unregister unregistered Movable!" );
	}
}

void Physics::RegisterCollisionMap( CollisionMapComponent& collisionMap )
{
	// check if tilesize matches
	if( m_tileSize == sf::Vector2u( 0, 0 ) )
	{
		m_tileSize = collisionMap.GetSize();
	}
	else if( m_tileSize != collisionMap.GetSize() )
	{
		throw std::runtime_error( "Tile size is not uniform!" );
	}
	// see if it's already registered
	if( !m_collisionMaps.insert( std::make_pair( collisionMap.GetPosition(), &collisionMap ) ).second )
	{
		Debug::Warning( "Trying to register multiple CollisionMaps at ", collisionMap.GetPosition().x, ", ", collisionMap.GetPosition().y, "!" );
	}
}

void Physics::UnregisterCollisionMap( CollisionMapComponent& collisionMap )
{
	if( m_collisionMaps.erase( collisionMap.GetPosition() ) == 0 )
	{
		Debug::Warning( "Trying to unregister unregistered CollisionMap at ", collisionMap.GetPosition().x, ", ", collisionMap.GetPosition().y, "!" );
	}
}

bool Physics::IsSolid( int x, int y ) const
{
	if( m_collisionMaps.empty() )
	{
		return false;
	}
	assert( m_tileSize != sf::Vector2u( 0, 0 ) );

	// Convert into tile + local offset

	// -9 / 10 = 0, fix that by turning -9 into -18 (and -1 into -10)
	sf::Vector2i tile(
		( x < 0 ? x - m_tileSize.x + 1 : x ) / m_tileSize.x,
		( y < 0 ? y - m_tileSize.y + 1 : y ) / m_tileSize.y
		);
	// -9 div 10 = -9, -10 div 10 = 0
	sf::Vector2u localCoord(
		x < 0 ? ( x % m_tileSize.x + m_tileSize.x ) % m_tileSize.x : x % m_tileSize.x,
		x < 0 ? ( y % m_tileSize.y + m_tileSize.y ) % m_tileSize.y : y % m_tileSize.y
		);
	auto it( m_collisionMaps.find( tile ) );

	// outside of map?
	if( it == m_collisionMaps.end() )
	{
		// all is nonsolid there
		return false;
	}
	else
	{
		return it->second->IsSolid( localCoord );
	}
}

void Physics::Update( const sf::Time& delta )
{
	// TODO: Physics
}
