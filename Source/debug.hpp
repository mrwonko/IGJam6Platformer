#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

namespace Debug
{
	struct FatalError : std::runtime_error
	{
		FatalError( const std::string& what ) : std::runtime_error( what ) {}
	};

	void Break();
	
	void Error( const std::string& message );

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

	inline std::string ConcatArgs( std::stringstream& ss )
	{
		return ss.str();
	}

	template< typename HEAD, typename... TAIL >
	inline std::string ConcatArgs( std::stringstream& ss, HEAD head, TAIL... tail )
	{
		ss << head;
		return ConcatArgs( ss, tail... );
	}

	template< typename... ARGS >
	inline void Error( ARGS... args )
	{
		std::stringstream ss;
		Error( ConcatArgs( ss, args... ) );
	}
}
