#include "textureManager.hpp"
#include "texture.hpp"
#include <cctype>

TextureManager::Ptr TextureManager::Get( const std::string& filename )
{
	std::string filenameLower;
	filenameLower.reserve( filename.size() );
	std::transform( filename.begin(), filename.end(), std::inserter( filenameLower, filenameLower.begin() ), std::tolower );

	// see if it's already loaded
	auto it = m_textureMap.find( filenameLower );
	if( it != m_textureMap.end() )
	{
		Ptr tex( it->second.lock() );
		if( tex )
		{
			return tex;
		}
	}
	// not yet loaded, or no longer loaded
	std::shared_ptr< Texture > tex( std::make_shared< Texture >() );
	if( tex->LoadFromFile( filename ) )
	{
		m_textureMap[ filenameLower ] = tex;
		return tex;
	}
	// file not found
	return nullptr;
}