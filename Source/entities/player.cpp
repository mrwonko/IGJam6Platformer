#include "player.hpp"
#include "../gameplaySettings.hpp"
#include "../components/position.hpp"
#include "../components/sprite.hpp"
#include "../components/movable.hpp"
#include "../components/rect.hpp"
#include "../components/health.hpp"
#include "../components/gravity.hpp"
#include "../components/moveIntent.hpp"

Player::Player( sf::Vector2i&& position, const sf::IntRect& rect, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics, const GameplaySettings& settings, std::function< void( ) > onPlayerKilled )
: m_position( std::make_shared< PositionComponent >( *this, std::move( position ) ) )
, m_moveIntent( std::make_shared< MoveIntentComponent >( *this, settings.GetMoveIntentParameters() ) )
{
	AddComponent( m_position );
	AddComponent( m_moveIntent );
	AddComponent( std::make_shared< SpriteComponent >( *this, texture, group ) );
	AddComponent( std::make_shared< RectComponent >( *this, rect ) );
	AddComponent( std::make_shared< MovableComponent >( *this, physics ) );
	AddComponent( std::make_shared< GravityComponent >( *this, settings.gravity ) );

	auto healthComponent( std::make_shared< HealthComponent >( *this, 1 ) );
	healthComponent->SetKillCallback( onPlayerKilled );
	AddComponent( healthComponent ); // TODO: Player Health > 1?

	InitComponents();
}

const sf::Vector2i& Player::GetPosition() const
{
	return m_position->GetPosition();
}
