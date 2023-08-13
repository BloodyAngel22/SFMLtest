#include "gameLogic.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(){
	Game game;
	Objects obj;
	Move move;
	srand(time(NULL));
	RenderWindow win(VideoMode(game.width, game.height, Style::Close), "Super Window");	
	win.setFramerateLimit(60);
	//Objects
	obj.heroO(hero); 
	obj.enemyO(enemy);

	Text text;
	Font font;
	yourText(text, font, 300, 250, 36);
	text.setString("Hello everyone");
	while (win.isOpen()) {
		Event ev;
		game.Logic(ev, win, game, hero, enemy, move, text, obj);
	}
	return 0;
}
