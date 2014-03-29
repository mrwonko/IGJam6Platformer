#pragma once

#include <SFML/System/Time.hpp>
#include <set>
#include <functional>

namespace Time
{
	void OnTimePassed( const sf::Time& delta );

	typedef std::function< void( const sf::Time& ) > Callback;

	/// @note does not take ownership, keep the Function alive! (You need to unregister it anyway.)
	void RegisterCallback( const Callback& callback );
	void UnregisterCallback( const Callback& callback );
}
