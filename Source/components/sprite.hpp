#pragma once

#include "../component.hpp"
#include <memory>
#include <string>
#include <SFML/Graphics/Sprite.hpp>

class Texture;

namespace sf
{
	class RenderTarget;
}

class SpriteComponent : public Component
{
public:
	/// Returns an entity's sprite component, if any, or a nullptr.
	static SpriteComponent* Get( const Entity& entity );

	SpriteComponent( Entity& owner, std::shared_ptr< Texture > texture );
	~SpriteComponent();

	void Draw( sf::RenderTarget& target );

	const std::string& GetType() const;

	// TODO: Animations
	// void SetAnimation( const std::string& name );

private:
	sf::Sprite m_sprite;
	std::shared_ptr< Texture > m_texture;
};
