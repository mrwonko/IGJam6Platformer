#pragma once

#include "../component.hpp"
#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics/Sprite.hpp>

class Texture;
class PositionComponent;
class SpriteGroup;

namespace sf
{
	class RenderTarget;
	class Time;
}

class SpriteComponent : public Component
{
public:
	SpriteComponent( Entity& owner, std::shared_ptr< const Texture > texture, SpriteGroup& group );
	~SpriteComponent();

	void Draw( sf::RenderTarget& target );

	const std::string& GetType( ) const;

	/// Returns an entity's sprite component, if any, or a nullptr.
	static std::shared_ptr< SpriteComponent > Get( const Entity& entity );

	void Init();

	// TODO: Animations
	// void SetAnimation( const std::string& name );
	// void Update( const sf::Time& delta );

private:
	sf::Sprite m_sprite;
	std::shared_ptr< const Texture > m_texture;
	std::shared_ptr< PositionComponent > m_position{ nullptr };
	SpriteGroup& m_group;
};
