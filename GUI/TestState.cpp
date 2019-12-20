#include "TestState.hpp"

TestState::TestState(Application* app){
	this->app = app;
}

void TestState::draw(const float dt){
	(void)dt;
	sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(100, 100));
    rect.setSize(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Green);

	app->window.draw(rect);
}

void TestState::update(const float dt){
	(void)dt;
}

void TestState::handleInput(){
	sf::Event event;

	while(this->app->window.pollEvent(event)){
		if(event.type == sf::Event::Closed)
			this->app->window.close();
	}
}

void TestState::pauseState(){

}