#include "component.hpp"
#include "entity.hpp"

Component::Component( Entity& owner )
: m_owner( owner )
{
}

Component::~Component()
{
}

std::shared_ptr< Component > Component::GetComponent( const Entity& entity, const std::string& type )
{
	return entity.GetComponent( type );
}

void Component::Init()
{
}
