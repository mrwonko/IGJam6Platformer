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

void Entity::AddComponent( std::shared_ptr< Component >&& component )
{
	std::string type( component->GetType() );
	if( !m_components.insert( std::make_pair( std::move( type ), std::move( component ) ) ).second )
	{
		Debug::Warning( "tried to register two ", type, "components!" );
	}
}

void Entity::InitComponents()
{
	for( auto& it : m_components )
	{
		it.second->Init();
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

std::shared_ptr< Component > Entity::GetComponent( const std::string& type ) const
{
	auto it( m_components.find( std::move( type ) ) );
	if( it == m_components.end() )
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}
