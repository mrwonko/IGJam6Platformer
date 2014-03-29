#include "colorConversion.hpp"

static std::vector< std::pair< PixelType, sf::Color > > s_pixelTypes
{ { PixelType::Air, sf::Color::White }
, { PixelType::Floor, sf::Color::Black }
, { PixelType::Killer, sf::Color::Red }
};

PixelType GetMatchingPixelType( const sf::Color& color )
{
	return MatchColor( s_pixelTypes, color );
}
