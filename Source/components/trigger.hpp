#pragma once

#include "../component.hpp"

#include <functional>
#include <SFML/Graphics/Rect.hpp>

class Physics;
class RectComponent;

class TriggerComponent : public Component
{
public:
	typedef std::function< void( Entity& ) > Callback;

	TriggerComponent( Entity& owner, Physics& physics, const Callback& onEnter );
	~TriggerComponent();

	void Init();

	static TriggerComponent* Get( const Entity& entity );
	const std::string& GetType() const;

	sf::IntRect GetGlobalRect() const;

	void OnEnter( Entity& other ) const;

private:
	Physics& m_physics;
	Callback m_onEnter;
	RectComponent* m_rect;
};
