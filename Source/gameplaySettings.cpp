#include "gameplaySettings.hpp"
#include "debug.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>

GameplaySettings::GameplaySettings( const std::string& levelpath )
: playerSize( 10, 32 )
, playerOffset( 0, 0 )
{
	std::ifstream file( levelpath + "/gameplay.txt" );
	if( !file )
	{
		Debug::Error( "Could not open ", levelpath, "/gameplay.txt!" );
	}
	std::string curLine;
	while( std::getline( file, curLine ) )
	{
		std::transform( curLine.begin(), curLine.end(), curLine.begin(), std::tolower );
		ParseLine( curLine );
	}
}

void GameplaySettings::ParseLine( const std::string& line )
{
	std::stringstream ss;
	ss << line;
	std::string type;
	ss >> type;
	if( !ss ) return;
	if( type == "screenwidth" )
	{
		ss >> screenWidth;
	}
	else if( type == "playerwidth" )
	{
		ss >> playerSize.x;
	}
	else if( type == "playerheight" )
	{
		ss >> playerSize.y;
	}
	else if( type == "playerspeed" )
	{
		ss >> playerSpeed;
	}
	else if( type == "playeroffsetx" )
	{
		ss >> playerOffset.x;
	}
	else if( type == "playeroffsety" )
	{
		ss >> playerOffset.y;
	}
	else if( type == "jumpheight" )
	{
		ss >> jumpHeight;
	}
	else if( type == "stepheight" )
	{
		ss >> stepHeight;
	}
	else if( type == "gravity" )
	{
		ss >> gravity;
	}
	else
	{
		Debug::Warning( "gameplay.txt includes unknown entry: ", type );
	}
	if( !ss )
	{
		Debug::Warning( "gameplay.txt includes invalid line: ", line );
	}
}

MoveIntentComponent::Parameters GameplaySettings::GetMoveIntentParameters() const
{
	MoveIntentComponent::Parameters parameters
	{
		playerSpeed,
		// jump impulse, arrived at via math
		int( std::round( std::sqrt( float( 2 * gravity * jumpHeight ) ) ) )
	};
	return parameters;
}
