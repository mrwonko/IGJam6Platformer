#include "level.hpp"
#include "vector2Comparator.hpp"
#include "entities/tile.hpp"

#include <set>
#include <cassert>

Level::Level( const std::string& levelpath, TextureManager& textureManager )
: m_textureManager( textureManager )
{
	LoadTiles( levelpath );
}

void Level::DrawTo( sf::RenderTarget& target )
{
	m_allSprites.DrawAll( target );
}

void Level::LoadTiles( const std::string& levelpath )
{
	typedef std::set< sf::Vector2i, Vector2iComparator > PositionSet;
	PositionSet triedPositions;
	PositionSet currentPositions; // tested in this iteration
	PositionSet nextPositions{ sf::Vector2i( 0, 0 ) }; // tested in the next iteration

	while( !nextPositions.empty() )
	{
		currentPositions = std::move( nextPositions );
		// nextPositions is now in a valid but undefined state.
		// put it in a defined state: empty.
		nextPositions.clear();
		for( const auto& currentPosition : currentPositions )
		{
			bool alreadyTried = !triedPositions.insert( currentPosition ).second;
			assert( !alreadyTried );
			if( alreadyTried )
			{
				continue;
			}
			if( LoadTile( levelpath, currentPosition ) )
			{
				// Tile exists, also try its neighbours
				for( int x = -1; x <= 1; x += 2 )
				{
					sf::Vector2i newPosition( currentPosition.x + x, currentPosition.y );
					if( triedPositions.find( newPosition ) == triedPositions.end() )
					{
						nextPositions.insert( newPosition );
					}
				}
				for( int y = -1; y <= 1; y += 2 )
				{
					sf::Vector2i newPosition( currentPosition.x, currentPosition.y + y );
					if( triedPositions.find( newPosition ) == triedPositions.end( ) )
					{
						nextPositions.insert( newPosition );
					}
				}
			}
		}
	}
}

bool Level::LoadTile( const std::string& levelpath, const sf::Vector2i& position )
{
	// Load Visuals and Collision
	Tile::Ptr tilePtr( Tile::LoadTile( levelpath, sf::Vector2i( position ), m_allSprites, m_physics, m_textureManager ) );
	if( !tilePtr )
	{
		return false;
	}
	m_entities.AddEntity( std::move( tilePtr ) );

	// load static images
	LoadImages( levelpath, position );

	// load gameplay entities
	LoadEntities( levelpath, position );

	return true;
}

void Level::LoadImages( const std::string& levelpath, const sf::Vector2i& position )
{
	// TODO
}

void Level::LoadEntities( const std::string& levelpath, const sf::Vector2i& position )
{
	// TODO
}
