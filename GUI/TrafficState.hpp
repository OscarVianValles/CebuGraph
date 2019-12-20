#pragma once
#ifndef TRAFFIC_STATE_HPP
#define TRAFFIC_STATE_HPP

#include <SFML/Graphics.hpp>

#include "StateManager.hpp"
#include "MapState.hpp"
#include "AddLocationState.hpp"

class TrafficState : public StateManager
{
	public:
		virtual void draw(const float dt);
		virtual void update(const float dt);
		virtual void handleInput();

		TrafficState(Application* app);
	private:
		bool isTextClicked(sf::Text text);

		sf::RectangleShape menu;

		sf::Texture texture;
		sf::Sprite menuSprite;
		std::vector<sf::Text> buttons;
		sf::Font font;

		const int NUM_BUTTONS = 3;

		void getDestination();
		void addLocation();
};

#endif