#include "usedLibrary.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

extern int state;
extern int counter;
extern RectangleShape hero;
extern RectangleShape enemy;

class Objects{
	public:
	void heroO(RectangleShape& hero);
	void enemyO(RectangleShape& enemy);
	int counter = 0, switcher = 1;
	int r = 255, g = 0, b = 0;
	void rainbow(RectangleShape& rect, int& switcher, int& counter, int& r, int& g, int& b, int speed);
};

class Move{
	public:
		bool up = 0, down = 0, left = 0, right = 0;
		float startSpeed = 0, maxSpeed = 5, curSpeed = 0;
		int state = 0;
};


class Game{
	public:
		int width = 800, height = 600;
	void heroMove(RectangleShape& hero, Move& move);
  void wanderingEnemy(RectangleShape& enemy, int& state, int& counter);
  void wallCheck(RectangleShape& rect,int speed, int stPosX, \
		int stPosY, int endPosX, int endPosY);
	void checkEvents(Event ev, RenderWindow& win);
	void draw(RenderWindow& win, RectangleShape hero, RectangleShape enemy, Text text);
	void Logic(Event ev, RenderWindow& win, Game game, RectangleShape& hero, \
		RectangleShape& enemy, Move& move, Text text, Objects& obj);
	bool checkCollision(RectangleShape rectA, RectangleShape rectB);
	
};


void yourText(Text& text, Font& font, int posX, int posY, int size);
