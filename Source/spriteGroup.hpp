#pragma once

#include <set>

class SpriteComponent;

namespace sf
{
	class RenderTarget;
}

class SpriteGroup
{
public:
	SpriteGroup() = default;
	~SpriteGroup() = default;
	SpriteGroup( const SpriteGroup& ) = delete;
	SpriteGroup( SpriteGroup&& ) = delete;
	SpriteGroup& operator=( const SpriteGroup& ) = delete;

	void RegisterSprite( SpriteComponent& sprite );
	void UnregisterSprite( SpriteComponent& sprite );
	void DrawAll( sf::RenderTarget& target ) const;

private:
	typedef std::set< SpriteComponent* > SpriteSet;
	SpriteSet m_sprites;
};
