#pragma once

#include "../component.hpp"

#include <SFML/Graphics/Rect.hpp>

class Physics;
class PositionComponent;

class RectComponent : public Component
{
public:
	RectComponent( Entity& owner, const sf::IntRect& rect );

	void Init();

	static std::shared_ptr< RectComponent > Get( const Entity& entity );
	const std::string& GetType() const;

	const sf::IntRect& GetLocalRect() const { return m_rect; }
	sf::IntRect GetGlobalRect() const;

private:
	sf::IntRect m_rect;
	std::shared_ptr< PositionComponent > m_position{ nullptr };
};
