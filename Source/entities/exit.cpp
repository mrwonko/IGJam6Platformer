#include "exit.hpp"
#include "../components/position.hpp"
#include "../components/sprite.hpp"
#include "../components/rect.hpp"
#include "../components/trigger.hpp"

Exit::Exit( sf::Vector2i&& position, const sf::IntRect& rect, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics )
: m_sprite( std::make_shared< SpriteComponent >( *this, texture, group ) )
, m_trigger( std::make_shared< TriggerComponent >( *this, physics ) )
{
	m_sprite->SetAnimation( "closed" );

	AddComponent( std::make_shared< PositionComponent >( *this, std::move( position ) ) );
	AddComponent( std::make_shared< RectComponent >( *this, rect ) );
	AddComponent( m_sprite );
	AddComponent( m_trigger );

	InitComponents();
}

void Exit::Open()
{
	m_sprite->SetAnimation( "open" );
	m_sprite->SetAnimationOverCallback(
		[ this ]( SpriteComponent& self )
		{
			self.SetAnimation( "opened" );
			self.SetAnimationOverCallback( nullptr );
			m_trigger->SetOnEnterCallback(
				[ this ]( Entity& ent )
				{
					if( ent.HasGroup( Group::Player ) && m_onExitCallback )
					{
						m_onExitCallback();
					}
				} );
		} );
}
