#pragma once

#include <memory>
#include <string>
#include <map>

class Texture;

class TextureManager
{
public:
	typedef std::shared_ptr< const Texture > Ptr;

	/// Returns a pointer to the given texture if it exists, or a null pointer otherwise.
	Ptr Get( const std::string& filename );

private:
	typedef std::map< std::string, std::weak_ptr< const Texture > > TextureMap;

	TextureMap m_textureMap;
};