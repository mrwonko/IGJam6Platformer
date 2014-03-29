#include "debug.hpp"

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

namespace Debug
{
	void Break()
	{
#		if defined(_WIN32) && defined(_DEBUG)
			DebugBreak();
#		endif
	}
}
