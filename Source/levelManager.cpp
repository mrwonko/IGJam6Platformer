#include "levelManager.hpp"
#include "level.hpp"
#include "debug.hpp"

#include <fstream>
#include <sstream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

LevelManager::LevelManager( const std::string& datapath )
: m_datapath( datapath )
{
	std::ifstream file( datapath + "levels.txt" );
	if( !file )
	{
		Debug::Error( "Could not load ", datapath, "levels.txt" );
	}
	std::string curLine;
	while( std::getline( file, curLine ) )
	{
		if( curLine == "" ) continue;

		m_levelNames.push_back( curLine );
	}
	if( m_levelNames.empty() )
	{
		Debug::Error( datapath, "levels.txt is empty!" );
	}
	if( !m_winTex.loadFromFile( datapath + "win.png" ) )
	{
		Debug::Error( "Could not load ", datapath, "win.png!" );
	}
	m_winSprite.setTexture( m_winTex, true );

	LoadCurrentLevel();
}

LevelManager::~LevelManager()
{
}

void LevelManager::DrawTo( sf::RenderTarget& target )
{
	if( m_curLevel ) m_curLevel->DrawTo( target );
	else if( m_done )
	{
		target.setView( sf::View( sf::FloatRect(
			0,
			0,
			float( m_winTex.getSize().x ),
			float( m_winTex.getSize().y )
			) ) );
		target.draw( m_winSprite );
	}
}

void LevelManager::RestartLevel()
{
	LoadCurrentLevel();
}

void LevelManager::NextLevel()
{
	if( m_done ) return;

	if( m_curLevelIndex + 1 >= m_levelNames.size() )
	{
		m_curLevel = nullptr;
		m_done = true;
	}
	else
	{
		++m_curLevelIndex;
		LoadCurrentLevel();
	}
}

void LevelManager::LoadCurrentLevel()
{
	// Old level is still in memory, so textures are not yet freed.
	std::unique_ptr< Level > level( new Level( m_datapath + m_levelNames[ m_curLevelIndex ], *this ) );
	m_curLevel = std::move( level );
}

void LevelManager::SetPlayerIntent( const MoveIntentComponent::Intent& intent )
{
	if( m_curLevel ) m_curLevel->SetPlayerIntent( intent );
}
