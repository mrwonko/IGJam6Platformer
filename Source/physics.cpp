#include "physics.hpp"
#include "debug.hpp"
#include "time.hpp"
#include "components/collisionMap.hpp"
#include "components/movable.hpp"
#include "components/trigger.hpp"
#include "components/health.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>

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
		Debug::Error( "Tile size is not uniform!" );
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

bool Physics::OnFloor( const sf::IntRect& rect ) const
{
	for( int x = rect.left; x < rect.left + rect.width; ++x )
	{
		if( GetPixelType( x, rect.top + rect.height ) != PixelType::Air )
		{
			return true;
		}
	}
	return false;
}

PixelType Physics::GetPixelType ( int x, int y ) const
{
	// prevent divide by zero
	if( m_collisionMaps.empty() )
	{
		return PixelType::Air;
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
		return PixelType::Air;
	}
	else
	{
		return it->second->GetPixelType( localCoord );
	}
}

void Physics::Update( const sf::Time& delta )
{
	// Move movables
	for( auto& movable : m_movables )
	{
		movable->Update( delta );
		Move( movable, delta );
	}
}

void operator|=( Physics::MoveResult& lhs, Physics::MoveResult rhs )
{
	lhs = Physics::MoveResult( int( lhs ) | int( rhs ) );
}

int operator&( Physics::MoveResult lhs, Physics::MoveResult rhs )
{
	return int( lhs ) & int( rhs );
}

void Physics::Move( MovableComponent* movable, const sf::Time& delta )
{
	// major axis is that with the bigger absolute velocity
	bool xMajor = true;
	int majorComponent = int( std::round( movable->GetVelocity().x * delta.asSeconds() ) );
	int minorComponent = int( std::round( movable->GetVelocity().y * delta.asSeconds() ) );
	sf::Vector2i majorAxis( majorComponent == 0 ? 0 : majorComponent / std::abs( majorComponent ), 0 );
	sf::Vector2i minorAxis( 0, minorComponent == 0 ? 0 : minorComponent / std::abs( minorComponent ) );
	if( std::abs( minorComponent ) > std::abs( majorComponent ) )
	{
		std::swap( minorComponent, majorComponent );
		std::swap( majorAxis, minorAxis );
		xMajor = false;
	}
	const int majorSign = majorComponent > 0 ? 1 : -1;
	const int minorSign = minorComponent > 0 ? 1 : -1;

	assert( std::abs( majorComponent ) >= std::abs( minorComponent ) );

	// Move along the major axis primarily and along the minor one when necessary.
	int prevTotalMinorOffset = 0;
	for( int major = 0; major != majorComponent; major += majorSign )
	{
		sf::Vector2i offset( majorAxis );
		const int totalMinorOffset = minorComponent * major / majorComponent;
		bool stop = false;
		if( totalMinorOffset != prevTotalMinorOffset )
		{
			assert( std::abs( totalMinorOffset - prevTotalMinorOffset ) == 1 );
			offset += minorAxis;
		}
		// One component may have been changed to 0 due to collision
		if( offset == sf::Vector2i( 0, 0 ) )
		{
			continue;
		}
		MoveResult result = IsMovePossible( movable->GetGlobalRect( ), offset );

		// TODO: Steps?
		if( result & MoveResult::BlockedHorizontally )
		{
			offset.x = 0;
			majorAxis.x = 0;
			minorAxis.x = 0;
			movable->GetVelocity().x = 0;
			stop |= movable->GetVelocity().y == 0;
		}
		if( result & MoveResult::BlockedVertically )
		{
			offset.y = 0;
			majorAxis.y = 0;
			minorAxis.y = 0;
			movable->GetVelocity().y = 0;
			stop |= movable->GetVelocity( ).x == 0;
		}
		if( result & MoveResult::Killed )
		{
			auto healthComp = HealthComponent::Get( movable->GetOwner() );
			if( healthComp ) healthComp->Kill();
		}
		movable->GetPosition() = movable->GetPosition() + offset;
	}
	// Fix for ending up just above the floor with huge downward velocity, leading to small jumps
	if( movable->OnFloor() )
	{
		// FIXME: delays getting killed, may prevent it?
		movable->GetVelocity().y = std::min( 0, movable->GetVelocity().y );
	}
}

Physics::MoveResult Physics::IsMovePossible( const sf::IntRect& rect, const sf::Vector2i direction )
{
	assert( std::abs( direction.x ) <= 1 );
	assert( std::abs( direction.y ) <= 1 );

	MoveResult result = MoveResult::Success;

	const int x = direction.x > 0 ? rect.left + rect.width - 1 : rect.left;
	const int y = direction.y > 0 ? rect.top + rect.height - 1 : rect.top;

	// Check horizontally
	if( direction.x != 0 )
	{
		for( int y = rect.top + direction.y; y < rect.top + direction.y + rect.height; ++y )
		{
			PixelType type = GetPixelType( x, y );
			if( type != PixelType::Air )
			{
				result |= MoveResult::BlockedHorizontally;
				if( type == PixelType::Killer )
				{
					result |= MoveResult::Killed;
				}
				break;
			}
		}
	}

	// Check vertically
	if( direction.y != 0 )
	{
		for( int x = rect.left + direction.x; x < rect.left+ direction.x + rect.width; ++x )
		{
			PixelType type = GetPixelType( x, y );
			if( type != PixelType::Air )
			{
				result |= MoveResult::BlockedVertically;
				if( type == PixelType::Killer )
				{
					result |= MoveResult::Killed;
				}
				break;
			}
		}
	}

	// Blocked horizontally? Then see if we can move vertically (1 pixel unchecked)
	if( result == MoveResult::BlockedHorizontally && direction.y != 0 )
	{
		const int x = direction.x > 0 ? rect.left : rect.left + rect.width - 1;
		PixelType type = GetPixelType( x, y );
		if( type != PixelType::Air )
		{
			result |= MoveResult::BlockedVertically;
			if( type == PixelType::Killer )
			{
				result |= MoveResult::Killed;
			}
		}
	}
	else if( result == MoveResult::BlockedVertically && direction.x != 0 )
	{
		const int y = direction.y > 0 ? rect.top : rect.top + rect.height - 1;
		PixelType type = GetPixelType( x, y );
		if( type != PixelType::Air )
		{
			result |= MoveResult::BlockedVertically;
			if( type == PixelType::Killer )
			{
				result |= MoveResult::Killed;
			}
		}
	}

	return result;
}

void Physics::FindCollisions()
{
	for( auto it = m_movables.begin(); it != m_movables.end(); ++it )
	{
		MovableComponent* movable = *it;
		sf::IntRect movableRect( movable->GetGlobalRect() );

		// Movable-Trigger collisions
		for( auto trigger : m_triggers )
		{
			if( movableRect.intersects( trigger->GetGlobalRect() ) )
			{
				trigger->OnEnter( movable->GetOwner() );
			}
		}

		// Movable-Movable collisions
		auto it2 = it; // start at next movable
		for( ++it2; it2 != m_movables.end( ); ++it2 )
		{
			MovableComponent* movable2 = *it2;
			if( movableRect.intersects( movable2->GetGlobalRect( ) ) )
			{
				movable->OnCollide( movable2->GetOwner( ) );
				movable2->OnCollide( movable->GetOwner( ) );
			}
		}
	}
}
