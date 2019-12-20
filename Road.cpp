#include "Road.hpp"

Road::Road(){
	sf::VertexArray line(sf::Quads, 4);
	lines = line;
	lines[0].position = sf::Vector2f(0, 0);
	lines[1].position = sf::Vector2f(0, 0);
	lines[2].position = sf::Vector2f(0, 0);
	lines[3].position = sf::Vector2f(0, 0);
	lines[0].color = sf::Color::Black;
	lines[1].color = sf::Color::Black;
	lines[2].color = sf::Color::Black;
	lines[3].color = sf::Color::Black;
	thickness = 5;
}

void Road::makeRoad(sf::Vector2f a, sf::Vector2f b){
	lines[0].position = sf::Vector2f(a.x - thickness, a.y);
	lines[1].position = sf::Vector2f(a.x +thickness, a.y);
	lines[2].position = sf::Vector2f(b.x + thickness, b.y);
	lines[3].position = sf::Vector2f(b.x - thickness, b.y);
}