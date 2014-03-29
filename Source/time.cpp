#include "time.hpp"
#include "debug.hpp"
#include <iostream>


namespace Time
{
	typedef std::set< const Time::Callback* > CallbackSet;

	static CallbackSet& GetCallbacks()
	{
		static CallbackSet s_callbacks;
		return s_callbacks;
	}

	void OnTimePassed( const sf::Time& time )
	{
		for( const auto& it : GetCallbacks() )
		{
			( *it )( time );
		}
	}

	void RegisterCallback( const Callback& callback )
	{
		if( GetCallbacks().find( &callback ) != GetCallbacks().end() )
		{
			Debug::Warning( "Tried to register Time callback twice!" );
		}
		else
		{
			GetCallbacks().insert( &callback );
		}
	}

	void UnregisterCallback( const Callback& callback )
	{
		auto it( GetCallbacks().find( &callback ) );
		if( it == GetCallbacks().end() )
		{
			Debug::Warning( "Tried to unregister unregistered Time callback!" );
		}
		else
		{
			GetCallbacks().erase( it );
		}
	}
}
