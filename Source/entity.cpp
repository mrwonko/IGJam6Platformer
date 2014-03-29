#include "entity.hpp"
#include "component.hpp"
#include "debug.hpp"
#include <iostream>

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::AddComponent( std::unique_ptr< Component >&& component )
{
	std::string type( component->GetType() );
	if( m_components.find( type ) != m_components.end() )
	{
		Debug::Warning( "tried to register two ", type, "components!" );
	}
	else
	{
		m_components.insert( { std::move( type ), std::move( component ) } );
	}
}

void Entity::AddGroup( Group group )
{
	m_groups.insert( group );
}

bool Entity::HasGroup( Group group ) const
{
	return m_groups.find( group ) != m_groups.end();
}

Component* Entity::GetComponent( const std::string& type ) const
{
	auto it( m_components.find( std::move( type ) ) );
	if( it == m_components.end() )
	{
		return nullptr;
	}
	else
	{
		return it->second.get();
	}
}
