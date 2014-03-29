#include "spriteGroup.h"
#include "debug.hpp"
#include "components/sprite.hpp"

void SpriteGroup::RegisterSprite( SpriteComponent& sprite )
{
	if( !m_sprites.insert( &sprite ).second )
	{
		Debug::Warning( "Duplicate Sprite registration!" );
	}
}

void SpriteGroup::UnregisterSprite( SpriteComponent& sprite )
{
	if( m_sprites.erase( &sprite ) == 0 )
	{
		Debug::Warning( "Unregistered Sprite unregistration!" );
	}
}

void SpriteGroup::DrawAll( sf::RenderTarget& target ) const
{
	for( auto it : m_sprites )
	{
		it->Draw( target );
	}
}
