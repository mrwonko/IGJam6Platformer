#pragma once

#include "../component.hpp"

#include <functional>
#include <SFML/Graphics/Rect.hpp>

class Physics;
class PositionComponent;

class TriggerComponent : public Component
{
public:
	typedef std::function< void( Entity& ) > Callback;

	TriggerComponent( Entity& owner, Physics& physics, const sf::IntRect& rect, const Callback& onEnter );
	~TriggerComponent();

	void Init();

	static TriggerComponent* Get( const Entity& entity );
	const std::string& GetType() const;

	const sf::IntRect& GetLocalRect() const { return m_rect; }
	sf::IntRect GetGlobalRect() const;

	void OnEnter( Entity& other ) const;

private:
	Physics& m_physics;
	Callback m_onEnter;
	sf::IntRect m_rect;
	PositionComponent* m_position;
};
