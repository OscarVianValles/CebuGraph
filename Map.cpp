#include "Map.hpp"

Map::Map(){
	size= 0;
	_graphs.createGraph(10);
	_texture.loadFromFile("content/smol.png");
	_select.loadFromFile("content/smol2.png");
	isSelected = false;
}

void Map::addLandmark(std::string name,int x, int y){
	_names.push_back(name);
	_graphs.addVertex(name);
	sf::Sprite temp;
	temp.setTexture(_texture);
	temp.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	temp.setPosition(sf::Vector2f(x, y));
	_landmarks.push_back(temp);
	_selected.push_back(false);
	size++;
}

void Map::addRoad(int a, int b,  int cost){
	_graphs.addEdge(a,b, cost);
}

sf::Sprite Map::drawLandmarks(int pos){
	return _landmarks[pos];
}

void Map::drawAll(sf::RenderWindow& window){
	int Rsize = _roads.size();
	for(int i = 0; i<Rsize; i++){
		window.draw(_roads[i].lines);
	}

	for(int i = 0; i<size;i++){
		window.draw(_landmarks[i]);
	}
}

void Map::makeRoad(int a, int b){
	Road temp;
	temp.makeRoad(_landmarks[a].getPosition(), _landmarks[b].getPosition(),a,b);
	_roads.push_back(temp);
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

void Map::changePath(int a, int b){
	int Rsize = _roads.size();
	for(int i = 0; i<Rsize; i++){
		if(_roads[i].source == a && _roads[i].destination == b)
			_roads[i].changePathColor();
	}
}

void Map::resetPath(){
	int Rsize = _roads.size();
	for(int i = 0; i<Rsize; i++){
		_roads[i].resetColor();
	}
}
