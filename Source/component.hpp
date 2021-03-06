#pragma once

#include <string>
#include <memory>

class Entity;

class Component
{
public:
	virtual ~Component();

	virtual const std::string& GetType() const = 0;

	virtual void Init();

	const Entity& GetOwner() const { return m_owner;  }
	Entity& GetOwner() { return m_owner;  }

protected:
	Component( Entity& owner );

	Component( const Component& ) = delete;
	Component( Component&& ) = delete;
	Component& operator=( const Component& ) = delete;

	Entity& m_owner;

	static std::shared_ptr< Component > GetComponent( const Entity& entity, const std::string& type );
};