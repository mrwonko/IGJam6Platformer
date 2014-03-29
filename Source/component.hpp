#pragma once

#include <string>

class Entity;

class Component
{
public:
	virtual ~Component();

	virtual const std::string& GetType() const = 0;

protected:
	Component( Entity& owner );

	Component( const Component& ) = delete;
	Component( Component&& ) = delete;
	Component& operator=( const Component& ) = delete;

	Entity& m_owner;

	static Component* GetComponent( const Entity& entity, const std::string& type );
};