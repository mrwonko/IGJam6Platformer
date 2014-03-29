#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>

struct GameplaySettings
{
	GameplaySettings( const std::string& levelpath );

	unsigned int screenWidth{ 320 }; // Breite des sichtbaren Ausschnitts in Pixeln
	sf::Vector2u playerSize; // Kollisions-Gr��e des Spielers in Pixeln
	sf::Vector2i playerOffset; // Abstand des Kollisionsrechtecks von oberer linker Ecke des Bilds
	unsigned int jumpHeight{ 24 }; // Sprungh�he in Pixeln(???)
	unsigned int stepHeight{ 4 }; // Stufen dieser H�he k�nnen ohne Sprung erklommen werden.
	unsigned int gravity{ 178 }; // Erdanziehungskraft in Pixeln pro Quadratsekunde

private:
	void ParseLine( const std::string& line );
};
