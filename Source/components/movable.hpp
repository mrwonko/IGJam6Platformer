#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "../component.hpp"

class PositionComponent;
class Physics;
class RectComponent;

class MovableComponent : public Component
{
public:
	static std::shared_ptr< MovableComponent > Get( const Entity& entity );

	MovableComponent( Entity& owner, Physics& physics );
	~MovableComponent();

	const std::string& GetType() const;

	void Init();

	sf::IntRect GetGlobalRect() const;
	sf::Vector2i GetPosition() const;

private:
	Physics& m_physics;
	std::shared_ptr< PositionComponent > m_position{ nullptr };
	std::shared_ptr< RectComponent > m_rect{ nullptr };
};
