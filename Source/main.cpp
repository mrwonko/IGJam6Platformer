#include <iostream>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

#include "entities/tile.hpp"
#include "physics.hpp"
#include "textureManager.hpp"
#include "spriteGroup.h"

int main( int argc, char** argv )
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Ridiculous Platformer", sf::Style::Close | sf::Style::Titlebar );

	Physics physics;
	TextureManager textureManager;
	SpriteGroup allSprites;
	Tile::Ptr tile0_0( Tile::LoadTile( "../data/testlevel", sf::Vector2i( 0, 0 ), allSprites, physics, textureManager ) );
	Tile::Ptr tile1_0( Tile::LoadTile( "../data/testlevel", sf::Vector2i( 1, 0 ), allSprites, physics, textureManager ) );
	while( window.isOpen() )
	{
		sf::Event ev;
		while( window.pollEvent( ev ) )
		{
			if( ev.type == sf::Event::Closed || ( ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape ) )
			{
				window.close();
			}
		}
		window.clear();
		allSprites.DrawAll( window );
		window.display();
	}
	return 0;
}