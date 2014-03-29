#include "component.hpp"
#include "entity.hpp"

Component::Component( Entity& owner )
: m_owner( owner )
{
}

Component::~Component()
{
}

Component* Component::GetComponent( const Entity& entity, const std::string& type )
{
	return entity.GetComponent( type );
}
