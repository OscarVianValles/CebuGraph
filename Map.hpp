#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include "Graph.hpp"
#include<SFML/Graphics.hpp>
#include <vector>

class Map
{
	public:
		sf::Texture _texture;
		sf::Texture _select;
		bool isSelected;
		Graph _graphs;
		std::vector<sf::Sprite> _landmarks;
		std::vector<std::string> _names;
		std::vector<bool> _selected;
	public:
		Map();
		//~Map();
		void addLandmark(std::string);
		void addRoad(int, int, int);
		sf::Sprite drawLandmarks(int);
		void drawAll(sf::RenderWindow&);

		int select(sf::Event, sf::RenderWindow&);
		int size;
};

#endif