#pragma once

#include "../entity.hpp"

#include <memory>
#include <functional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Texture;
class SpriteGroup;
class Physics;
class SpriteComponent;
class TriggerComponent;

/**
	Exit: Starts closed, playing "closed" animation in a loop.
	When Open() is called, plays the "open" animation, then loops "opened" and waits for enter events.
	Once somebody enters, it calls the OnExit callback.
**/
class Exit : public Entity
{
public:
	typedef std::function< void() > OnExitCallback;

	Exit( sf::Vector2i&& position, const sf::IntRect& rect, std::shared_ptr< const Texture > texture, SpriteGroup& group, Physics& physics );

	void SetOnExitCallback( OnExitCallback callback ) { m_onExitCallback = callback; }
	void Open();

private:
	OnExitCallback m_onExitCallback;
	std::shared_ptr< SpriteComponent > m_sprite;
	std::shared_ptr< TriggerComponent > m_trigger;
};