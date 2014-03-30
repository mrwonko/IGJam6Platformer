#include "level.hpp"
#include "vector2Comparator.hpp"
#include "debug.hpp"
#include "textureManager.hpp"
#include "colorConversion.hpp"
#include "entities/tile.hpp"
#include "entities/player.hpp"
#include "entities/staticSprite.hpp"

#include <fstream>
#include <set>
#include <cassert>
#include <algorithm>
#include <cctype>

#include <SFML/Graphics/Image.hpp>

Level::Level( const std::string& levelpath, TextureManager& textureManager )
: m_gameplaySettings( levelpath )
, m_textureManager( textureManager )
{
	EntityDefinitions entityDefinitions( LoadEntities( levelpath ) );
	ImageDefinitions imageDefinitions( LoadImages( levelpath ) );
	LoadTiles( levelpath, imageDefinitions, entityDefinitions );
	if( !m_player )
	{
		Debug::Error( levelpath, " contains no player!" );
	}
}

Level::~Level()
{
}

void Level::DrawTo( sf::RenderTarget& target )
{
	m_background.DrawAll( target );
	m_images.DrawAll( target );
	m_entitySprites.DrawAll( target );
	m_playerSprite.DrawAll( target );
}

void Level::LoadTiles( const std::string& levelpath, const ImageDefinitions& imageDefinitions, const EntityDefinitions& entityDefinitions )
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
			if( LoadTile( levelpath, currentPosition, imageDefinitions, entityDefinitions ) )
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

bool Level::LoadTile( const std::string& levelpath, const sf::Vector2i& position, const ImageDefinitions& imageDefinitions, const EntityDefinitions& entityDefinitions )
{
	// Load Visuals and Collision
	Tile::Ptr tilePtr( Tile::LoadTile( levelpath, sf::Vector2i( position ), m_background, m_physics, m_textureManager ) );
	if( !tilePtr )
	{
		return false;
	}
	m_entities.AddEntity( std::move( tilePtr ) );

	// load static images
	LoadTileImages( levelpath, position, imageDefinitions );

	// load gameplay entities
	LoadTileEntities( levelpath, position, entityDefinitions );

	return true;
}

void Level::LoadTileImages( const std::string& levelpath, const sf::Vector2i& position, const ImageDefinitions& imageDefinitions )
{
	sf::Image img;
	{
		std::stringstream name;
		name << levelpath << "/" << position.x << "_" << position.y << ".images.png";
		if( !img.loadFromFile( name.str() ) )
		{
			return;
		}
		if( imageDefinitions.empty( ) )
		{
			Debug::Warning( levelpath, "/", position.x, "_", position.y, ".images.png exists but there's no images.txt!" );
			return;
		}
		for( unsigned int x = 0; x < img.getSize().x; ++x )
		{
			for( unsigned int y = 0; y < img.getSize().y; ++y )
			{
				const sf::Color color = img.getPixel( x, y );

				// ignore transparent pixels
				if( color.a < 128 ) continue;

				auto texture = MatchColor( imageDefinitions, color );
				m_entities.AddEntity( std::unique_ptr< StaticSprite >( new StaticSprite( sf::Vector2i( x, y ), texture, m_images ) ) );
			}
		}
	}
}

void Level::LoadTileEntities( const std::string& levelpath, const sf::Vector2i& position, const EntityDefinitions& entityDefinitions )
{
	sf::Image img;
	{
		std::stringstream name;
		name << levelpath << "/" << position.x << "_" << position.y << ".game.png";
		if( !img.loadFromFile( name.str( ) ) )
		{
			return;
		}
		if( entityDefinitions.empty( ) )
		{
			Debug::Warning( levelpath, "/", position.x, "_", position.y, ".game.png exists but there's no game.txt!" );
			return;
		}
		for( unsigned int x = 0; x < img.getSize( ).x; ++x )
		{
			for( unsigned int y = 0; y < img.getSize( ).y; ++y )
			{
				const sf::Color color = img.getPixel( x, y );

				sf::Vector2i globalPosition(
					img.getSize().x * position.x + x,
					img.getSize().y * position.y + y
					);

				// ignore transparent pixels
				if( color.a < 128 ) continue;

				EntityDefinition def = MatchColor( entityDefinitions, color );
				switch( def.type )
				{
				case EntityType::Collectible:
					// TODO
					break;
				case EntityType::Enemy:
					// TODO
					break;
				case EntityType::Exit:
					// TODO
					break;
				case EntityType::Player:
					if( m_player )
					{
						Debug::Error( "Multiple players in ", levelpath, "!" );
					}
					m_player = std::unique_ptr< Player >( new Player(
						std::move( globalPosition ),
						def.rect,
						def.texture,
						m_playerSprite,
						m_physics,
						m_gameplaySettings,
						[ this ](){ } // TODO: Exit Level!
						) );
					break;
				default:
					Debug::Error( "Internal Error, invalid entity type?" );
					break;
				}
			}
		}
	}
}

static sf::IntRect ReadRect( std::istream& is )
{
	sf::IntRect rect;
	is >> rect.left;
	is >> rect.top;
	is >> rect.width;
	is >> rect.height;
	return rect;
}

static sf::Color ReadColor( std::istream& is )
{
	sf::Color color;
	int temp;
	is >> temp;
	color.r = temp;
	is >> temp;
	color.g = temp;
	is >> temp;
	color.b = temp;
	return color;
}

Level::EntityDefinitions Level::LoadEntities( const std::string& levelpath )
{
	std::ifstream file( levelpath + "/game.txt" );
	if( !file )
	{
		Debug::Error( "Could not open ", levelpath, "/game.txt!" );
	}

	EntityDefinitions definitions;

	std::string curLine;
	while( std::getline( file, curLine ) )
	{
		if( curLine == "" )
		{
			continue;
		}
		std::stringstream ss;
		ss << curLine;

		sf::Color color( ReadColor( ss ) );

		std::string type;
		ss >> type;

		if( !ss )
		{
			Debug::Error( "Invalid line in ", levelpath, "/game.txt: ", curLine );
		}

		EntityDefinition def;

		std::transform( type.begin( ), type.end( ), type.begin( ), std::tolower );
		bool validType = true;
		if( type == "player" )
		{
			def.type = EntityType::Player;
			def.texture = m_textureManager.Get( levelpath + "/player.png" );
			if( !def.texture )
			{
				Debug::Error( "Could not load ", levelpath, "/player.png!" );
			}
			def.rect.width = m_gameplaySettings.playerSize.x;
			def.rect.height = m_gameplaySettings.playerSize.y;
			def.rect.left = m_gameplaySettings.playerOffset.x;
			def.rect.top = m_gameplaySettings.playerOffset.y;
		}
		else if( type == "exit" )
		{
			def.type = EntityType::Exit;
			def.rect = ReadRect( ss );
			def.texture = m_textureManager.Get( levelpath + "/exit.png" );
			if( !def.texture )
			{
				Debug::Error( "Could not load ", levelpath, "/exit.png!" );
			}
		}
		else if( type == "collectible" )
		{
			def.type = EntityType::Collectible;
			def.rect = ReadRect( ss );
			def.texture = m_textureManager.Get( levelpath + "/collectible.png" );
			if( !def.texture )
			{
				Debug::Error( "Could not load ", levelpath, "/collectible.png!" );
			}
		}
		else if( type == "enemy" )
		{
			def.type = EntityType::Enemy;
			def.rect = ReadRect( ss );
			std::string texName;
			ss >> texName;
			ss >> def.walkingBehaviour;
			ss >> def.attackType;
			if( texName == "" )
			{
				Debug::Error( "Invalid enemy definition in ", levelpath, "/game.txt: ", curLine );
			}
			texName = levelpath + "/" + texName;
			def.texture = m_textureManager.Get( texName );
			if( !def.texture )
			{
				Debug::Error( "Could not load enemy texture ", texName, "!" );
			}
		}
		else
		{
			validType = false;
		}
		if( !ss )
		{
			Debug::Error( "Invalid line in ", levelpath, "/game.txt: ", curLine );
		}
		if( !validType )
		{
			Debug::Error( "Invalid type ", type, " in line ", curLine, " in ", levelpath, "/game.txt!" );
		}
		definitions.push_back( std::make_pair( def, color ) );
	}
	return definitions;
}

Level::ImageDefinitions Level::LoadImages( const std::string& levelpath )
{
	std::ifstream file( levelpath + "/images.txt" );
	if( !file )
	{
		return ImageDefinitions();
	}

	ImageDefinitions definitions;

	std::string curLine;
	while( std::getline( file, curLine ) )
	{
		if( curLine == "" )
		{
			continue;
		}
		std::stringstream ss;
		ss << curLine;

		sf::Color color( ReadColor( ss ) );

		std::string texName;
		ss >> texName;

		if( !ss )
		{
			Debug::Error( "Invalid line in ", levelpath, "/images.txt: ", curLine );
		}

		texName = levelpath + "/" + texName;
		auto texture = m_textureManager.Get( texName );
		if( !texture )
		{
			Debug::Error( "Could not load image ", texName, "!" );
		}

		definitions.push_back( std::make_pair( texture, color ) );
	}

	return definitions;
}

void Level::SetPlayerIntent( const MoveIntentComponent::Intent& intent )
{
	if( m_player )
	{
		auto intComp = MoveIntentComponent::Get( *m_player );
		assert( intComp );
		intComp->SetIntent( intent );
	}
}
