#pragma once
#ifndef MAP_STATE_HPP
#define MAP_STATE_HPP

#include <SFML/Graphics.hpp>

#include "StateManager.hpp"
#include "AddLocationState.hpp"
#include "TrafficState.hpp"
#include "Map.hpp"
#include "Ribbon.hpp"

class MapState : public StateManager
{
	public:
		virtual void draw(const float dt);
		virtual void update(const float dt);
		virtual void handleInput();

		MapState(Application* app);
	private:
		bool isTextClicked(sf::Text text);

		sf::Texture texture;
		sf::Sprite menuSprite;
		std::vector<sf::Text> buttons;
		sf::Font font;

		const int NUM_BUTTONS = 3;

		void addLocation();
		void updateTraffic();

		Ribbon source;
};

#endif