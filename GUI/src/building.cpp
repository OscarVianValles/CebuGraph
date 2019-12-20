#include "building.hpp"

const std::string imageSource = "content/smol.png";
const std::string imageSource2 = "content/smol2.png";

building::building(){

}

building::building(int x, int y){
	bTexture.loadFromFile(imageSource);
	selectTexture.loadFromFile(imageSource2);
	bSprite.setTexture(bTexture);
	posX = x;
	posY = y;
	bSprite.setPosition(posX, posY);
	isSelected = false;
}

void building::build(int x, int y){
	bTexture.loadFromFile(imageSource);
	selectTexture.loadFromFile(imageSource2);
	bSprite.setTexture(bTexture);
	posX = x;
	posY = y;
	bSprite.setPosition(posX, posY);
	isSelected = false;
}

sf::Sprite building::getSprite(){
	return bSprite;
}

void building::click(sf::Event event, sf::RenderWindow& window){
	if(event.type == sf::Event::MouseButtonPressed){
		switch (event.key.code){
		case sf::Mouse::Left:
			if (bSprite.getPosition().x  + bSprite.getTexture()->getSize().x >= sf::Mouse::getPosition(window).x && bSprite.getPosition().x <= sf::Mouse::getPosition(window).x
				&& bSprite.getPosition().y <= sf::Mouse::getPosition(window).y && bSprite.getPosition().y + bSprite.getTexture()->getSize().y >= sf::Mouse::getPosition(window).y){
				if(!isSelected){
					bSprite.setTexture(selectTexture);
					isSelected = true;
				}
			}
			else{
					bSprite.setTexture(bTexture);
					isSelected= false;
				}
			break;

		default:
			break;
		}
	}
}