#ifndef RIBBON_HPP
#define RIBBON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Ribbon
{
	public:
		sf::RectangleShape _ribbon;
		sf::Font _font;
		sf::Text _source;
		sf::Text _destination;
	public:
		Ribbon();
		void update(std::string);
		void draw(sf::RenderWindow&);
};

#endif