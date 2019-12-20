#include "Map.hpp"

Map::Map(){
	size= 0;
	_graphs.createGraph(10);
	_texture.loadFromFile("content/smol.png");
	_select.loadFromFile("content/smol2.png");
	isSelected = false;
}

void Map::addLandmark(std::string name){
	_names.push_back(name);
	_graphs.addVertex(name);
	sf::Sprite temp;
	temp.setTexture(_texture);
	temp.setPosition(sf::Vector2f(512, 384));
	_landmarks.push_back(temp);
	_selected.push_back(false);
	size++;
}

void Map::addRoad(int a, int b,  int cost){
	_graphs.addEdge(a,b, cost);

	_landmarks[a].setPosition(_landmarks[b].getPosition().x, _landmarks[b].getPosition().y + cost);
}

sf::Sprite Map::drawLandmarks(int pos){
	return _landmarks[pos];
}

void Map::drawAll(sf::RenderWindow& window){
	for(int i = 0; i<size;i++){
		window.draw(_landmarks[i]);
	}
}

int Map::select(sf::Event event, sf::RenderWindow& window){

	if(event.type == sf::Event::MouseButtonPressed){
		for(int i = 0; i<size;i++){
			switch (event.key.code){
			case sf::Mouse::Left:
				if (_landmarks[i].getPosition().x  + _landmarks[i].getTexture()->getSize().x >= sf::Mouse::getPosition(window).x && _landmarks[i].getPosition().x <= sf::Mouse::getPosition(window).x
					&& _landmarks[i].getPosition().y <= sf::Mouse::getPosition(window).y && _landmarks[i].getPosition().y + _landmarks[i].getTexture()->getSize().y >= sf::Mouse::getPosition(window).y){
					if(!isSelected){
						_landmarks[i].setTexture(_select);
						_selected[i] = true;
					}
				}
				else{
						_landmarks[i].setTexture(_texture);
						_selected[i] = false;
					}
				break;

			default:
				break;
			}
		}
	}

	for(int i = 0; i<size ; i++){
		if(_selected[i])
			return i;
	}
	return -1;
}
