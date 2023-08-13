#include "gameLogic.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <string>

RectangleShape hero;
void Objects::heroO(RectangleShape& hero){	
	hero.setSize({50,50});
	hero.setPosition({200, 200});
	hero.setFillColor(Color::Red);
}

RectangleShape enemy;
void Objects::enemyO(RectangleShape& enemy){
	enemy.setSize({50,50});
	enemy.setPosition({650, 400});
	enemy.setFillColor(Color::Yellow);
}

void yourText(Text& text, Font& font, int posX, int posY, int size){
	if (!font.loadFromFile("SuperFoods.ttf"))
		std::cout << "not found font" << std::endl;
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(Color::White);
	text.setPosition(posX, posY);
}
