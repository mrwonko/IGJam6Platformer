#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>

class Texture
{
public:
	bool LoadFromFile( const std::string& filename );

	const sf::Texture& GetTexture( ) const { return m_texture; }

private:
	sf::Texture m_texture;
};
