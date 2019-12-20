#pragma once
#ifndef ADD_LOCATION_STATE_HPP
#define ADD_LOCATION_STATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "StateManager.hpp"
#include "MapState.hpp"
#include "TrafficState.hpp"

class AddLocationState : public StateManager
{
	public:
		virtual void draw(const float dt);
		virtual void update(const float dt);
		virtual void handleInput();

		AddLocationState(Application* app);


		void addLandmark(int, sf::Event);
	private:
		bool isTextClicked(sf::Text text);

		sf::Texture texture;
		sf::Sprite menuSprite;
		std::vector<sf::Text> buttons;
		sf::Font font;

		const int NUM_BUTTONS = 3;

		void getDestination();
		void updateTraffic();

		std::string playerInput;
		sf::Text playerText;

		std::string location;
		sf::Text locationText;

		int stateInput;

};

#endif