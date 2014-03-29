#include "texture.hpp"

bool Texture::LoadFromFile( const std::string& filename )
{
	if( !m_texture.loadFromFile( filename ) )
	{
		return false;
	}
	// TODO: Animations
	return true;
}
