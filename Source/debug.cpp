#include "debug.hpp"
#include <stdexcept>

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

	void Error( const std::string& message )
	{
		std::cerr << message << std::endl;
#		ifdef _WIN32
			MessageBox( NULL, message.c_str(), "Error!", MB_OK | MB_ICONERROR | MB_TASKMODAL );
#		endif
		Break();
		throw std::runtime_error( message );
	}
}
