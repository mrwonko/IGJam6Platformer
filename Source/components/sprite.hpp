#pragma once

#include "../component.hpp"
#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics/Sprite.hpp>

class Texture;
class PositionComponent;

namespace sf
{
	class RenderTarget;
	class Time;
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

	void Init();

	// TODO: Animations
	// void SetAnimation( const std::string& name );
	// void Update( const sf::Time& delta );

private:
	sf::Sprite m_sprite;
	std::shared_ptr< Texture > m_texture;
	PositionComponent* m_position{ nullptr };
};
