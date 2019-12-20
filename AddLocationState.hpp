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


		void addLandmarkState(sf::Event);
	private:
		bool isTextClicked(sf::Text text);

		sf::RectangleShape menu;

		sf::Texture texture;
		sf::Sprite menuSprite;
		std::vector<sf::Text> buttons;
		sf::Font font;

		const int NUM_BUTTONS = 3;

		void getDestination();
		void updateTraffic();

		//all
		std::string status;
		sf::Text statusG;
		//landmark
		std::string name, x, y;
		sf::Text buttonLG, nameG, xG, yG;
		int landmarkState;

		//state
		int state; //1 = land. 2 = road, 0 = none(select)
};

#endif