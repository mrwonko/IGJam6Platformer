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

	virtual ~Entity();

	void MarkForDeletion() { m_markedForDeletion = true;  }
	bool MarkedForDeletion() const { return m_markedForDeletion;  }

	bool HasGroup( Group group ) const;

protected:
	Entity();

	void AddComponent( std::shared_ptr< Component >&& component );
	/// Call once all components are registered so they can do initialization that requires interaction with each other
	void InitComponents();
	void AddGroup( Group group );

	/// Returns the given type of Component, if available, or a nullptr
	std::shared_ptr< Component > GetComponent( const std::string& type ) const;

private:
	Entity( const Entity& ) = delete;
	Entity( Entity&& ) = delete;
	Entity& operator=( const Entity& ) = delete;

	typedef std::map< std::string, std::shared_ptr< Component > > ComponentMap;
	typedef std::set< Group > GroupSet;

	ComponentMap m_components;
	GroupSet m_groups;
	bool m_markedForDeletion{ false };
};