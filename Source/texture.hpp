#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <string>
#include <map>

class Texture
{
public:
	struct Animation
	{
		unsigned int startFrame;
		unsigned int length;
		sf::Time frameTime;
	};

	bool LoadFromFile( const std::string& filename );

	const sf::Texture& GetTexture() const { return m_texture; }

	sf::IntRect GetFrameRect( unsigned int frame ) const;

	Animation GetAnimation( const std::string& name ) const;

private:
	sf::Texture m_texture;
	sf::Vector2u m_frameSize;
	std::map< std::string, const Animation > m_animations;
};
