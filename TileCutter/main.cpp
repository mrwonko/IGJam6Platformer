#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>

enum
{
	TILE_SIZE = 512
};

int main( int argc, char** argv )
{
	if( argc < 2 )
	{
		std::cerr << "no command line argument!" << std::endl;
		return 1;
	}

	std::string path( argv[ 1 ] );
	std::string::size_type lastSep = path.find_last_of( "/\\" );
	std::string dir, file;

	if( lastSep == std::string::npos )
	{
		dir = "";
		file = path;
	}
	else
	{
		dir = path.substr( 0, lastSep + 1 );
		file = path.substr( lastSep + 1 );
	}
	sf::Image img;
	if( !img.loadFromFile( argv[ 1 ] ) ) return 1;

	int x = 0;
	for( unsigned int tileY = 0; tileY * TILE_SIZE < img.getSize().y; ++tileY )
	{
		for( unsigned int tileX = 0; tileX * TILE_SIZE < img.getSize().x ; ++tileX )
		{
			sf::Image tile;
			tile.create( TILE_SIZE, TILE_SIZE, sf::Color( 0, 0, 0, 0 ) );
			for( unsigned int y = 0; y < TILE_SIZE; ++y )
			{
				const unsigned int absY = tileY * TILE_SIZE + y;
				if( absY >= img.getSize().y ) break;

				for( unsigned int x = 0; x < TILE_SIZE; ++x )
				{
					const unsigned int absX = tileX * TILE_SIZE + x;
					if( absX >= img.getSize().x ) break;

					tile.setPixel( x, y, img.getPixel( absX, absY ) );
				}
			}
			std::stringstream ss;
			ss << dir << tileX << '_' << tileY << file;

			tile.saveToFile( ss.str() );
		}
	}
	return 0;
}