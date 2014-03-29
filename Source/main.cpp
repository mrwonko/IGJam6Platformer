#include <iostream>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

int main( int argc, char** argv )
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Ridiculous Platformer", sf::Style::Close | sf::Style::Titlebar );
	while( window.isOpen() )
	{
		sf::Event ev;
		while( window.pollEvent( ev ) )
		{
			if( ev.type == sf::Event::Closed || ( ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape ) )
			{
				window.close();
			}
			window.clear();
			window.display();
		}
	}
	return 0;
}