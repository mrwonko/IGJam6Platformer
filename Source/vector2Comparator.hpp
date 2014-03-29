#pragma once


template< class T >
struct Vector2Comparator
{
	bool operator() ( const sf::Vector2< T >& lhs, const sf::Vector2< T >& rhs ) const
	{
		return lhs.x < rhs.x || ( lhs.x == rhs.x && lhs.y < rhs.y );
	}
};

typedef Vector2Comparator< int > Vector2iComparator;
typedef Vector2Comparator< unsigned > Vector2uComparator;
typedef Vector2Comparator< float > Vector2fComparator;
