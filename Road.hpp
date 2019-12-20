#ifndef ROAD_HPP
#define ROAD_HPP

#include <SFML/Graphics.hpp>

class Road{
	public:
		Road();
		int source, destination;
		sf::VertexArray lines;
		int thickness;
		void makeRoad(sf::Vector2f, sf::Vector2f,int,int);
		void changePathColor();
		void resetColor();

};

#endif