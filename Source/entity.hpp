#pragma once

#include <map>
#include <set>
#include <memory>
#include <string>

class Entity
{
	friend class Component; // may GetComponent()
public:
	enum class Group
	{
		Player,
		Enemy
	};

	virtual ~Entity( );

	bool HasGroup( Group group ) const;

protected:
	Entity();

	void AddComponent( std::unique_ptr< Component >&& component );
	void AddGroup( Group group );

	/// Returns the given type of Component, if available, or a nullptr
	Component* GetComponent( const std::string& type ) const;

private:
	Entity( const Entity& ) = delete;
	Entity( Entity&& ) = delete;
	Entity& operator=( const Entity& ) = delete;

	typedef std::map< std::string, std::unique_ptr< Component > > ComponentMap;
	typedef std::set< Group > GroupSet;

	ComponentMap m_components;
	GroupSet m_groups;
};