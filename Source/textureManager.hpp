#pragma once

#include <memory>
#include <string>
#include <map>

class Texture;

class TextureManager
{
public:
	/// Returns a pointer to the given texture if it exists, or a null pointer otherwise.
	std::shared_ptr< Texture > Get( const std::string& filename );

private:
	typedef std::map< std::string, std::weak_ptr< Texture > > TextureMap;

	TextureMap m_textureMap;
};