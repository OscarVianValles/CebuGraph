#include "Ribbon.hpp"

Ribbon::Ribbon(){
	_ribbon.setSize(sf::Vector2f(800,100));
	_ribbon.setOrigin(sf::Vector2f(400, 50));
	_ribbon.setPosition(sf::Vector2f(512, 150));
	_ribbon.setFillColor(sf::Color::White);
	_ribbon.setOutlineColor(sf::Color::Black);
	_ribbon.setOutlineThickness(5);

	_font.loadFromFile("content/OPM.otf");
	_source.setFont(_font);
	_source.setPosition(sf::Vector2f(150, 130));
	_source.setFillColor(sf::Color::Black);
	_source.setCharacterSize(24);
	_source.setString("Source: ");

	_destination.setFont(_font);
	_destination.setPosition(sf::Vector2f(250, 130));
	_destination.setFillColor(sf::Color::Black);
	_destination.setCharacterSize(24);
}

void Ribbon::draw(sf::RenderWindow& window){
	window.draw(_ribbon);
	window.draw(_source);
	window.draw(_destination);
}

void Ribbon::update(std::string name){
	_destination.setString(name);
}