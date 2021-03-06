#include <iostream>
#include <string>
#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "levelManager.hpp"
#include "time.hpp"
#include "debug.hpp"

static const sf::Time s_frameTime( sf::milliseconds( 20 ) );

int main( int argc, char** argv )
{
	try
	{
		bool fullscreen = false;
		unsigned int width = 800;
		unsigned int height = 600;
		{
			std::ifstream resConfig( "resolution.txt" );
			resConfig >> width;
			resConfig >> height;
			resConfig >> fullscreen;
		}

		sf::Uint32 windowStyle = sf::Style::Close | sf::Style::Titlebar;
		if( fullscreen ) windowStyle |= sf::Style::Fullscreen;
		sf::RenderWindow window( sf::VideoMode( width, height ), "Ridiculous Platformer", windowStyle );
		window.setMouseCursorVisible( false );
		window.clear();
		window.display();

		LevelManager levelManager( "../data/" );

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
				else if( ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::F1 )
				{
					levelManager.NextLevel();
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
				levelManager.SetPlayerIntent( intent );
			}

			// Draw
			if( updated )
			{
				window.clear( );
				levelManager.DrawTo( window );
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
		return 1;
	}
}