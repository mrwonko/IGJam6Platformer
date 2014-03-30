#include <iostream>
#include <string>

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "level.hpp"
#include "textureManager.hpp"
#include "time.hpp"
#include "debug.hpp"

static const sf::Time s_frameTime( sf::milliseconds( 20 ) );

int main( int argc, char** argv )
{
	try
	{
		sf::Time totalElapsed;
		unsigned int counter;
		std::function< void( const sf::Time& ) > timeTest = [ &totalElapsed, &counter ]( const sf::Time& delta )
		{
			totalElapsed += delta;
			++counter;
			if( counter % 50 == 0 )
			{
				std::cout << totalElapsed.asSeconds( ) << " seconds elapsed" << std::endl;
			}
		};
		Time::RegisterCallback( timeTest );

		sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Ridiculous Platformer", sf::Style::Close | sf::Style::Titlebar );

		TextureManager textureManager;
		Level testlevel( "../data/testlevel", textureManager );

		sf::Clock clock;
		sf::Time lastFrameTime;

		while( window.isOpen() )
		{
			// Handle Events
			sf::Event ev;
			while( window.pollEvent( ev ) )
			{
				if( ev.type == sf::Event::Closed || ( ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape ) )
				{
					window.close();
				}
			}

			// Update game at fixed framerate
			sf::Time elapsedTime = clock.getElapsedTime() - lastFrameTime;
			bool updated = false;
			while( elapsedTime > s_frameTime )
			{
				Time::OnTimePassed( s_frameTime );
				elapsedTime -= s_frameTime;
				lastFrameTime += s_frameTime;
				updated = true;
			}

			// Draw
			if( updated )
			{
				window.clear( );
				testlevel.DrawTo( window );
				window.display( );
			}
			else
			{
				sf::sleep( s_frameTime - elapsedTime );
			}
		}
		return 0;
	}
	// "normal" runtime error exit (usually broken assets)
	catch( Debug::FatalError )
	{
	}
}