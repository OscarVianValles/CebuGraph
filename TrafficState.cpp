#include "TrafficState.hpp"
#include <iostream>

TrafficState::TrafficState(Application* app){
	//background
	texture.loadFromFile("content/mapsample.jpg");
	menuSprite.setTexture(texture);

	//menu
	menu.setSize(sf::Vector2f(800, 600));
	menu.setFillColor(sf::Color::White);
	menu.setOutlineColor(sf::Color::Black);
	menu.setOutlineThickness(5);
	menu.setPosition(sf::Vector2f(100,100));

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

	buttons[2].setFillColor(sf::Color::Red);
	this->app = app;
}

void TrafficState::handleInput(){
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
				if (isTextClicked(buttons[1]))
					buttons[1].setFillColor(sf::Color::Blue);
				else
					buttons[1].setFillColor(sf::Color::Black);
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
		else if (isTextClicked(buttons[1]))
            addLocation();
	}
}

void TrafficState::update(const float dt){
	(void)dt;
}

void TrafficState::draw(const float dt){
	(void)dt;

	app->window.draw(menuSprite);

	app->window.draw(menu);

	for(auto x : buttons)
		app->window.draw(x);
}

bool TrafficState::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(app->window)))
        return true;


    //Otherwise, don't do anything
    return false;
}

void TrafficState::getDestination(){
	app->pushState(new MapState(app));
}

void TrafficState::addLocation(){
	app->pushState(new AddLocationState(app));

}