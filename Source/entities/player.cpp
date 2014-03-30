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
, m_halfSize( settings.playerOffset + ( sf::Vector2i( settings.playerSize.x, settings.playerSize.y ) / 2 ) )
{
	AddComponent( m_position );
	AddComponent( m_moveIntent );
	AddComponent( std::make_shared< SpriteComponent >( *this, texture, group ) );
	AddComponent( std::make_shared< RectComponent >( *this, rect ) );

	auto healthComponent( std::make_shared< HealthComponent >( *this, 1 ) );
	healthComponent->SetKillCallback( onPlayerKilled );
	AddComponent( healthComponent ); // TODO: Player Health > 1?
	std::weak_ptr< HealthComponent > weakHC( healthComponent );

	auto movableComponent = std::make_shared< MovableComponent >( *this, physics );
	movableComponent->SetMaxStep( settings.stepHeight );
	// die on contact with enemy
	movableComponent->SetCollideCallback(
		[ weakHC ]( Entity& other )
		{
			if( other.HasGroup( Entity::Group::Enemy ) )
			{
				auto healthComp( weakHC.lock() );
				if( healthComp ) healthComp->Kill();
			}
		} );
	AddComponent( movableComponent );

	AddComponent( std::make_shared< GravityComponent >( *this, settings.gravity ) );

	AddGroup( Group::Player );

	InitComponents();
}

const sf::Vector2i& Player::GetPosition() const
{
	return m_position->GetPosition();
}

sf::Vector2f Player::GetCenter() const
{
	return sf::Vector2f(
		float( GetPosition().x ) + m_halfSize.x,
		float( GetPosition().y ) + m_halfSize.y
		);
}
