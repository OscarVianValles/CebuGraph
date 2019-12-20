#include <SFML/Graphics.hpp>
#include <iostream>

class building{
	private:
		sf::Texture bTexture;
		sf::Texture selectTexture;
		sf::Sprite bSprite;
		int posX, posY;
		bool isSelected;
	public:
		building();
		building(int, int);

		void build(int, int);

		sf::Sprite getSprite();
		void click(sf::Event, sf::RenderWindow&);
};

