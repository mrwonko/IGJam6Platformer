#pragma once

#include <cmath>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <SFML/Graphics/Color.hpp>

enum class PixelType : char
{
	Air,
	Floor,
	Killer,
	Count
};

PixelType GetMatchingPixelType( const sf::Color& color );

// Compare two pairs by the distance of the color in their second element to a given color
template< class T >
struct ColorPairCompare
{
	ColorPairCompare( const sf::Color& color ) : m_color( color ) {}
	int distance( const sf::Color& color )
	{
		return std::abs( int( color.r ) - int( m_color.r ) )
			+ std::abs( int( color.g ) - int( m_color.g ) )
			+ std::abs( int( color.b ) - int( m_color.b ) );
	}

	bool operator()( const std::pair< T, sf::Color >& lhs, const std::pair< T, sf::Color >& rhs )
	{
		return distance( lhs.second ) < distance( rhs.second );
	}
private:
	sf::Color m_color;
};

template< class T >
const T& MatchColor( const std::vector< std::pair< T, sf::Color > >& definitions, const sf::Color& color )
{
	return std::min_element( definitions.begin(), definitions.end(), ColorPairCompare< T >( color ) )->first;
}
