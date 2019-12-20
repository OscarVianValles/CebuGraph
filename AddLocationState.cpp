#include "AddLocationState.hpp"
#include <iostream>

AddLocationState::AddLocationState(Application* app){
	state = 0;
	landmarkState = 0;

	//background
	texture.loadFromFile("content/mapsample.jpg");
	menuSprite.setTexture(texture);

	//menu
	menu.setSize(sf::Vector2f(800, 300));
	menu.setFillColor(sf::Color::White);
	menu.setOutlineColor(sf::Color::Black);
	menu.setOutlineThickness(5);
	menu.setPosition(sf::Vector2f(100,250));

	//text
	sf::Text text;
	font.loadFromFile("content/OPM.otf");
	text.setFont(font);
    text.setPosition(50, 50);
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Black);   // set the color
    text.setStyle(sf::Text::Bold); // set the text style

	//all
	statusG.setFont(font);
	statusG.setPosition(110,350);
	statusG.setFillColor(sf::Color::Black);

	//Landmark
	buttonLG.setFont(font);
	buttonLG.setPosition(110,250);
	buttonLG.setFillColor(sf::Color::Black);
	buttonLG.setString("ADD LANDMARK");

	nameG.setFont(font);
	nameG.setPosition(110,450);
	nameG.setFillColor(sf::Color::Black);

	xG.setFont(font);
	xG.setPosition(110,450);
	xG.setFillColor(sf::Color::Black);

	yG.setFont(font);
	yG.setPosition(110,450);
	yG.setFillColor(sf::Color::Black);

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
				if(state==0){
					if (isTextClicked(buttonLG))
						buttonLG.setFillColor(sf::Color::Blue);
					else
						buttonLG.setFillColor(sf::Color::Black);
				}
				break;
			case sf::Event::TextEntered:
				if(state == 1){
					addLandmarkState(event);
				}
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
		else if (isTextClicked(buttonLG) && state == 0){
            state = 1;
			landmarkState = 1;
			buttonLG.setFillColor(sf::Color::Red);
			statusG.setString("Enter Landmark Name: ");
		}
	}
}

void AddLocationState::addLandmarkState(sf::Event event){
	switch(landmarkState){
		case 1:
			if(event.text.unicode < 128 && event.text.unicode >64)
				{
					name +=event.text.unicode;
					nameG.setString(name);
				}
			else if(event.text.unicode == 8)
			{
				if(!name.empty()){
				name.erase(name.size() - 1);
				nameG.setString(name);
				}
			}
			else if(event.text.unicode == 32){
				if(!name.empty()){
					statusG.setString("Enter Position (X):");
					landmarkState = 2;
				}
				else
					statusG.setString("Enter Landmark Name pls:");
			}
			break;
		case 2:
			if(event.text.unicode < 58 && event.text.unicode >47)
				{
					x +=event.text.unicode;
					xG.setString(x);
				}
			else if(event.text.unicode == 8)
			{
				if(!x.empty()){
				x.erase(x.size() - 1);
				xG.setString(x);
				}
			}
			else if(event.text.unicode == 32){
				if(!name.empty()){
					statusG.setString("Enter Position (Y):");
					landmarkState = 3;
				}
				else
					statusG.setString("Enter Valid Positon (X):");
			}
			break;
		case 3:
			if(event.text.unicode < 58 && event.text.unicode >47)
				{
					y +=event.text.unicode;
					yG.setString(y);
				}
			else if(event.text.unicode == 8)
			{
				if(!y.empty()){
				y.erase(y.size() - 1);
				yG.setString(y);
				}
			}
			else if(event.text.unicode == 32){
				if(!name.empty()){
					statusG.setString("Creating Landmark . . . .\n\n\nPress Space to Continue");
					cebu.addLandmark(name, atoi(x.c_str()), atoi(y.c_str()));
					landmarkState = 4;
				}
				else
					statusG.setString("Enter Valid Positon (Y):");
			}
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

	app->window.draw(menu);
	if(state == 0){
		app->window.draw(buttonLG);
	}
	else if(state == 1){
		if(landmarkState == 1){
			app->window.draw(nameG);
		}
		else if(landmarkState == 2){
			app->window.draw(xG);
		}
		else if(landmarkState == 3){
			app->window.draw(yG);
		}
		app->window.draw(statusG);
		app->window.draw(buttonLG);
	}
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