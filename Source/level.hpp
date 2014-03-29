#pragma once

#include "spriteGroup.hpp"
#include "entityManager.hpp"
#include "physics.hpp"

#include <string>
#include <SFML/System/Vector2.hpp>

class TextureManager;

namespace sf
{
	class RenderTarget;
}

class Level
{
public:
	Level( const std::string& levelpath, TextureManager& textureManager );
	~Level() = default;
	Level( const Level& ) = delete;
	Level( Level&& ) = delete;
	Level& operator=( const Level& ) = delete;

	void DrawTo( sf::RenderTarget& target );
private:
	void LoadTiles( const std::string& levelpath );
	bool LoadTile( const std::string& levelpath, const sf::Vector2i& position );
	void LoadImages( const std::string& levelpath, const sf::Vector2i& position );
	void LoadEntities( const std::string& levelpath, const sf::Vector2i& position );


	TextureManager& m_textureManager;
	// Mind the order! Entities must be destroyed before managers (Physics, SpriteGroup) since they'll unregister on destruction!
	SpriteGroup m_allSprites;
	Physics m_physics;
	EntityManager m_entities;
};
