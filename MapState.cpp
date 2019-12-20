#include "MapState.hpp"
#include <iostream>

Map cebu;

MapState::MapState(Application* app){
	//buildings
	// cebu.addLandmark("SOGO");
	// cebu.addLandmark("UP Cebu");

	// cebu.addRoad(0, 1, 200);
	// cebu.addRoad(1,0, 100);
	//background
	texture.loadFromFile("content/mapsample.jpg");
	menuSprite.setTexture(texture);

	//text
	sf::Text text;
	font.loadFromFile("content/OPM.otf");
	text.setFont(font);
    text.setPosition(50, 50);
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Black);   // set the color
    text.setStyle(sf::Text::Bold); // set the text style

	 //set positions of things
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons.push_back(text);
        buttons[i].setPosition(text.getPosition().x + i * 250, text.getPosition().y );
    }

	//Since it's only 3 text its fine to just manually set each...
    buttons[0].setString("Get Directions");
    buttons[1].setString("Add Landmark");
    buttons[2].setString("Update Traffic");

	buttons[0].setFillColor(sf::Color::Red);
	this->app = app;
}

void MapState::handleInput(){
	sf::Event event;

	while(app->window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				app->window.close();
				break;
			case sf::Event::MouseMoved:
				if (isTextClicked(buttons[1]))
					buttons[1].setFillColor(sf::Color::Blue);
				else
					buttons[1].setFillColor(sf::Color::Black);
				if (isTextClicked(buttons[2]))
					buttons[2].setFillColor(sf::Color::Blue);
				else
					buttons[2].setFillColor(sf::Color::Black);
				break;
			default:
				break;
		}
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

			int selected  = cebu.select(event, app->window);
			if(selected>-1)
				source.update(cebu._names[selected]);
			else
				source.update("Select");
			if (isTextClicked(buttons[1]))
            	addLocation();
			else if (isTextClicked(buttons[2]))
            	updateTraffic();
	}
}

void MapState::update(const float dt){
	(void)dt;
}

void MapState::draw(const float dt){
	(void)dt;
	app->window.draw(menuSprite);

	for(auto x : buttons)
		app->window.draw(x);

	cebu.drawAll(app->window);
	source.draw(app->window);
}

bool MapState::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(app->window)))
        return true;


    //Otherwise, don't do anything
    return false;
}

void MapState::addLocation(){
	app->pushState(new AddLocationState(app));
}

void MapState::updateTraffic(){
	//app->pushState()
	app->pushState(new TrafficState(app));
}