#include "AddLocationState.hpp"
#include <iostream>

AddLocationState::AddLocationState(Application* app){
	stateInput = 0;
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

	playerText.setFont(font);
	playerText.setPosition(60,300);
	playerText.setFillColor(sf::Color::Red);
	playerText.setString("enter Location: ");

	locationText.setFont(font);
	locationText.setPosition(60,600);
	locationText.setFillColor(sf::Color::Red);
	locationText.setString("enter Location: ");

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

	buttons[1].setFillColor(sf::Color::Red);
	this->app = app;


}

void AddLocationState::handleInput(){
	sf::Event event;

	while(app->window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				app->window.close();
				break;
			case sf::Event::MouseMoved:
				if (isTextClicked(buttons[0]))
					buttons[0].setFillColor(sf::Color::Blue);
				else
					buttons[0].setFillColor(sf::Color::Black);
				if (isTextClicked(buttons[2]))
					buttons[2].setFillColor(sf::Color::Blue);
				else
					buttons[2].setFillColor(sf::Color::Black);
				break;
			 case sf::Event::TextEntered:
			 	if(event.text.unicode == 32){
					 stateInput++;
				 }
				 addLandmark(stateInput, event);
				break;
			default:
				break;
		}
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//changestate
		if (isTextClicked(buttons[0]))
            getDestination();
		else if (isTextClicked(buttons[2]))
            updateTraffic();
	}
}

void AddLocationState::addLandmark(int state, sf::Event event){

		std::cout<<stateInput<<std::endl;
	switch(state){
		case 0://vertex
			if(event.text.unicode < 128 && event.text.unicode >64)
				{
					playerInput +=event.text.unicode;
					playerText.setString(playerInput);
				}
			else if(event.text.unicode == 8)
			{
				if(!playerInput.empty()){
				playerInput.erase(playerInput.size() - 1);
				playerText.setString(playerInput);
				}
			}
			break;
		case 1:
			if(cebu.size == 0){
				cebu.addLandmark(playerInput);
				stateInput = 3;
				playerText.setString("root added");
			}
			else{
				cebu.addLandmark(playerInput);
				playerText.setString("add location");
				playerInput.erase();
				stateInput = 2;
			}
			break;
		case 2:
			if(event.text.unicode < 58 && event.text.unicode >47)
				{
					location +=event.text.unicode;
					locationText.setString(location);
				}
			else if(event.text.unicode == 8)
			{
				if(!location.empty()){
				location.erase(location.size() - 1);
				locationText.setString(location);
				}
			}
			break;
		case 3:
			locationText.setString("location added");
			cebu.addRoad(1, 0, 100);
			break;
		default:
			getDestination();
			break;
	}

}

void AddLocationState::update(const float dt){
	(void)dt;
}

void AddLocationState::draw(const float dt){
	(void)dt;
	app->window.draw(menuSprite);

	for(auto x : buttons)
		app->window.draw(x);

	app->window.draw(playerText);
	app->window.draw(locationText);
}

bool AddLocationState::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(app->window)))
        return true;


    //Otherwise, don't do anything
    return false;
}

void AddLocationState::getDestination(){
	app->pushState(new MapState(app));
}

void AddLocationState::updateTraffic(){
	app->pushState(new TrafficState(app));
}