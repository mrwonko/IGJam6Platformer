#include <iostream>
#include <string>

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
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

				MoveIntentComponent::Intent intent;
				intent.jump = 
					sf::Keyboard::isKeyPressed( sf::Keyboard::Space )
					|| sf::Keyboard::isKeyPressed( sf::Keyboard::Up )
					|| sf::Keyboard::isKeyPressed( sf::Keyboard::W );
				intent.left =
					sf::Keyboard::isKeyPressed( sf::Keyboard::A )
					|| sf::Keyboard::isKeyPressed( sf::Keyboard::Left );
				intent.right =
					sf::Keyboard::isKeyPressed( sf::Keyboard::D )
					|| sf::Keyboard::isKeyPressed( sf::Keyboard::Right );
				testlevel.SetPlayerIntent( intent );
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