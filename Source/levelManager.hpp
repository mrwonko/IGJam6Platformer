#pragma once

#include <string>
#include <vector>
#include <memory>

#include "textureManager.hpp"
#include "components/moveIntent.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Level;

namespace sf
{
	class RenderTarget;
}

class LevelManager
{
public:
	LevelManager( const std::string& datapath );
	~LevelManager();
	LevelManager( const LevelManager& ) = delete;
	LevelManager( LevelManager&& ) = delete;
	LevelManager& operator=( const LevelManager& ) = delete;

	void DrawTo( sf::RenderTarget& target );

	TextureManager& GetTextureManager() { return m_textureManager; }

	void RestartLevel();

	void NextLevel();

	void SetPlayerIntent( const MoveIntentComponent::Intent& intent );

private:
	void LoadCurrentLevel();

	const std::string m_datapath;
	std::unique_ptr< Level > m_curLevel;
	unsigned int m_curLevelIndex{ 0 };
	std::vector< std::string > m_levelNames;

	bool m_done{ false };

	sf::Texture m_winTex;
	sf::Sprite m_winSprite;

	TextureManager m_textureManager;
};
