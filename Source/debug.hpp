#pragma once

#include <iostream>

namespace Debug
{

	void Break();

	inline void Warning()
	{
		std::cerr << std::endl;
		Break();
	}

	template< typename HEAD, typename... TAIL >
	inline void Warning( HEAD head, TAIL... tail )
	{
		std::cerr << head;
		Warning( tail... );
	}
}
