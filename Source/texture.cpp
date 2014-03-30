#include "texture.hpp"
#include "debug.hpp"

#include <fstream>
#include <sstream>

bool Texture::LoadFromFile( const std::string& filename )
{
	if( !m_texture.loadFromFile( filename ) )
	{
		return false;
	}
	m_frameSize = m_texture.getSize();

	std::ifstream file( filename + ".animations.txt" );
	// No animations?
	if( !file )
	{
		return true;
	}

	// animations and stuff.
	std::string curLine;
	if( !std::getline( file, curLine ) )
	{
		Debug::Error( filename, ".animations.txt is empty! Needs at least frame dimensions!" );
	}
	else
	{
		std::stringstream ss;
		ss << curLine;
		ss >> m_frameSize.x >> m_frameSize.y;
		if( !ss )
		{
			Debug::Error( filename, ".animations.txt did not contain proper dimensions: ", curLine );
		}
	}
	while( std::getline( file, curLine ) )
	{
		if( curLine == "" ) continue;
		std::stringstream ss;
		ss << curLine;

		std::string name;
		Animation anim;
		ss >> name;
		unsigned int fps;
		ss >> anim.startFrame >> anim.length >> fps;
		anim.frameTime = sf::seconds( 1.f ) / float( fps );

		if( !ss )
		{
			Debug::Error( filename, ".animations.txt contains invalid line: ", curLine );
		}

		if( !m_animations.emplace( name, anim ).second )
		{
			Debug::Error( filename, ".animations.txt contains duplicate animation: ", name );
		}
	}
	return true;
}

sf::IntRect Texture::GetFrameRect( unsigned int frame ) const
{
	const unsigned int framesPerLine = m_texture.getSize().x / m_frameSize.x;
	return sf::IntRect(
		( frame % framesPerLine ) * m_frameSize.x,
		( frame / framesPerLine ) * m_frameSize.y,
		m_frameSize.x,
		m_frameSize.y
		);
}

Texture::Animation Texture::GetAnimation( const std::string& name ) const
{
	auto it = m_animations.find( name );
	if( it == m_animations.end() )
	{
		//Debug::Warning( "Image lacks animation ", name ); //nah, that just clutters cerr
		return Animation
		{
			0,
			1,
			sf::seconds( 1.f )
		};
	}
	else
	{
		return it->second;
	}
}
