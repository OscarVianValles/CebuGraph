#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include "Graph.hpp"
#include<SFML/Graphics.hpp>
#include <vector>
#include "Road.hpp"

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
		std::vector<Road> _roads;
	public:
		Map();
		//~Map();
		void addLandmark(std::string, int, int);
		void addRoad(int, int, int);
		sf::Sprite drawLandmarks(int);
		void drawAll(sf::RenderWindow&);
		void makeRoad(int, int);
		int select(sf::Event, sf::RenderWindow&);

		void changePath(int, int);
		void resetPath();
		int size;
};

#endif