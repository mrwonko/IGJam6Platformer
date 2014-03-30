#pragma once

#include "../component.hpp"
#include "../texture.hpp"
#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class PositionComponent;
class SpriteGroup;

namespace sf
{
	class RenderTarget;
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

	typedef std::function< void( SpriteComponent& ) > AnimationOverCallback;

	void SetAnimation( const std::string& name );
	const std::string& GetAnimation() const { return m_curAnimationName;  }
	void LoopAnimation( bool loop ) { m_loopAnimation = loop; }
	void SetAnimationOverCallback( AnimationOverCallback callback ) { m_animationOverCallback = callback; }

private:
	void UpdateAnimation( const sf::Time& delta );

	sf::Sprite m_sprite;
	std::shared_ptr< const Texture > m_texture;
	std::shared_ptr< PositionComponent > m_position{ nullptr };
	SpriteGroup& m_group;

	bool m_loopAnimation{ true };
	unsigned int m_curFrame{ 0 };
	std::string m_curAnimationName;
	Texture::Animation m_curAnimation;
	sf::Time m_frameTime;
	std::function< void( const sf::Time& ) > m_animationTimerCallback;
	AnimationOverCallback m_animationOverCallback;
};
