#pragma once

#include "spriteGroup.hpp"
#include "entityManager.hpp"
#include "physics.hpp"
#include "gameplaySettings.hpp"
#include "components/moveIntent.hpp"

#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class TextureManager;
class Texture;
class Player;

namespace sf
{
	class RenderTarget;
}

class Level
{
public:
	Level( const std::string& levelpath, TextureManager& textureManager );
	~Level();
	Level( const Level& ) = delete;
	Level( Level&& ) = delete;
	Level& operator=( const Level& ) = delete;

	void DrawTo( sf::RenderTarget& target );

	void SetPlayerIntent( const MoveIntentComponent::Intent& intent );
private:
	enum class EntityType
	{
		Player,
		Exit,
		Collectible,
		Enemy
	};
	struct EntityDefinition
	{
		EntityType type;
		std::shared_ptr< const Texture > texture;
		sf::IntRect rect;
		unsigned int walkingBehaviour;
		unsigned int attackType;
	};

	typedef std::vector< std::pair< EntityDefinition, sf::Color > > EntityDefinitions;
	typedef std::vector< std::pair< std::shared_ptr< const Texture >, sf::Color > > ImageDefinitions;

	ImageDefinitions LoadImages( const std::string& levelpath );
	EntityDefinitions LoadEntities( const std::string& levelpath );

	void LoadTiles( const std::string& levelpath, const ImageDefinitions& imageDefinitions, const EntityDefinitions& entityDefinitions );
	bool LoadTile( const std::string& levelpath, const sf::Vector2i& position, const ImageDefinitions& imageDefinitions, const EntityDefinitions& entityDefinitions );
	void LoadTileImages( const std::string& levelpath, const sf::Vector2i& position, const ImageDefinitions& imageDefinitions );
	void LoadTileEntities( const std::string& levelpath, const sf::Vector2i& position, const EntityDefinitions& entityDefinitions );

	GameplaySettings m_gameplaySettings;
	TextureManager& m_textureManager;

	// Mind the order! Entities must be destroyed before managers (Physics, SpriteGroup) since they'll unregister on destruction!

	// Managers
	SpriteGroup m_background;
	SpriteGroup m_images;
	SpriteGroup m_entitySprites;
	SpriteGroup m_playerSprite;
	Physics m_physics;

	// Entities
	std::unique_ptr< Player > m_player{ nullptr };
	EntityManager m_entities;

};
