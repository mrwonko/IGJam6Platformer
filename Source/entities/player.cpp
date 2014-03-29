#include "player.hpp"
#include "../components/position.hpp"
#include "../components/sprite.hpp"
#include "../components/movable.hpp"
#include "../components/rect.hpp"

Player::Player( sf::Vector2i&& position, const sf::IntRect& rect, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics, const GameplaySettings& settings )
: m_position( std::make_shared< PositionComponent >( *this, std::move( position ) ) )
{
	AddComponent( m_position );
	AddComponent( std::make_shared< SpriteComponent >( *this, texture, group ) );
	AddComponent( std::make_shared< RectComponent >( *this, rect ) );
	AddComponent( std::make_shared< MovableComponent >( *this, physics ) );
	// TODO: controller
	// TODO: input
	// TODO: gravity
	InitComponents();
}

const sf::Vector2i& Player::GetPosition() const
{
	return m_position->GetPosition();
}
