#include "gameLogic.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;

int state = 0;
int counter = 0;


void Game::Logic(Event ev, RenderWindow& win, Game game, RectangleShape& hero, \
		RectangleShape& enemy, Move& move, Text text, Objects& obj){
	game.checkEvents(ev, win);	
	game.heroMove(hero, move);
	game.wanderingEnemy(enemy, state, counter);
	game.wallCheck(hero, move.maxSpeed, 0,0, game.width, game.height);
	game.wallCheck(enemy, 2, game.width/2, game.height/2, game.width, game.height);
/* 	if (checkCollision(hero, enemy)){

	} */
	obj.rainbow(hero, obj.switcher, obj.counter, obj.r, obj.g,obj.b, 2);
	game.draw(win, hero, enemy, text);
}

void Game::heroMove(RectangleShape& hero, Move& m){
		if (Keyboard::isKeyPressed(Keyboard::A)){
			m.left = 1;
			m.state = LEFT;
			m.down = m.up = m.right = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)){
			m.right = 1;
			m.state = RIGHT;
			m.down = m.up = m.left = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)){
			m.up = 1;
			m.state = UP;
			m.down = m.left = m.right = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)){
			m.down = 1;
			m.state = DOWN;
			m.up = m.left = m.right = 0;
		}
		if (!Keyboard::isKeyPressed(Keyboard::W) and !Keyboard::isKeyPressed(Keyboard::S)\
				and !Keyboard::isKeyPressed(Keyboard::A) and !Keyboard::isKeyPressed(Keyboard::D)){
			m.down = m.up = m.right = m.left = 0;
		}
		if (m.left or m.down or m.right or m.up){	
			if (m.curSpeed < m.maxSpeed)
				m.curSpeed += 0.12;
		if (m.left){
			hero.move(-m.curSpeed, 0);
		}

		if (m.right){
			hero.move(m.curSpeed, 0);
		}
		if (m.up){
			hero.move(0, -m.curSpeed);
		}
		if (m.down){
			hero.move(0, m.curSpeed);
		}
		}
		if (!m.down and !m.up and !m.left and !m.right and m.state != 0){
			if (m.state == UP){
				hero.move(0, -m.curSpeed);
			}	
			if (m.state == DOWN){
				hero.move(0, m.curSpeed);
			}	
			if (m.state == LEFT){
				hero.move(-m.curSpeed, 0);
			}	
			if (m.state == RIGHT){
				hero.move(m.curSpeed, 0);
			}	
				m.curSpeed -= 0.12;
				if (m.curSpeed <= m.startSpeed){
					m.curSpeed = 0;
					m.state = 0;
				}
		}
}

void Game::checkEvents(Event ev, RenderWindow& win){
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
			if (ev.type == Event::KeyPressed){
				if (ev.key.code == Keyboard::Escape)
					win.close();
			}
		}
}

void Game::draw(RenderWindow& win, RectangleShape hero, RectangleShape enemy, Text text){
		win.clear(Color::Black);
		win.draw(enemy);
		win.draw(hero);
		win.draw(text);
		win.display();
}

void Game::wanderingEnemy(RectangleShape& enemy, int& state, int& counter){
	int speed = 2;
	if (state == 0)
		state = rand() % 4 + 1;
	if (state == UP){
			enemy.move(0, -speed);
			counter++;
	}
	else if (state == DOWN){
			enemy.move(0,speed);
			counter++;
	}
	else if (state == RIGHT){
			enemy.move(speed,0);
			counter++;
	}
	else if (state == LEFT){
			enemy.move(-speed,0);
			counter++;
	}
	if (counter >= rand() % 40 + 30){
		state = 0;
		counter = 0;
	}
}

void Game::wallCheck(RectangleShape& rect,int speed, int stPosX, \
		int stPosY, int endPosX, int endPosY){
	Vector2f pos = rect.getPosition();
	Vector2f size = rect.getSize();
	if (pos.x + size.x > endPosX)
		rect.setPosition(endPosX - size.x, pos.y);
	if (pos.x < stPosX)
		rect.setPosition(stPosX, pos.y);
	if (pos.y < stPosY)
		rect.setPosition(pos.x, stPosY);
	if (pos.y + size.y > endPosY)
		rect.setPosition(pos.x, endPosY - size.y);	
}

bool Game::checkCollision(RectangleShape rectA, RectangleShape rectB){	
	if	(rectA.getGlobalBounds().intersects(rectB.getGlobalBounds()))
		return true;
	return false;
}

void Objects::rainbow(RectangleShape& rect, int& switcher, int& counter, int& r, int& g, int& b, int speed){
	if (switcher == 8){
		switcher = 1;
	}
	
	switch (switcher) {	
	case 1:	
	//red 255 0 0
	rect.setFillColor(Color(r,g,b));
	g+=speed;
	if (g >= 165)
		switcher++;
	break;
	case 2:
	//orange 255 165 0
	rect.setFillColor(Color(r,g,b));	
		g+=speed;
	if (g >= 250)
		switcher++;
	break;
	case 3:
	//yellow 255 255 0
	rect.setFillColor(Color(r,g,b));	
	r-=speed;
	if (r<=5)
		switcher++;
	break;
	case 4:
	//green 0 255 0
	rect.setFillColor(Color(r,g,b));
	if (r<=61)
		r+=speed;
	if (g>=165)
		g-=speed;
	if(b<=250)
		b+=speed;
	if (r >= 61 and g<=165 and b>=250)
		switcher++;
	break;
	case 5:
	//cyan 66 170 255
	rect.setFillColor(Color(r,g,b));
	if(r>=5)
		r-=speed;
	if (g>=5)
		g-=speed;
	if(b<=250)
		b+=speed;
	if(r <= 5 and g <= 5 and b >= 250)
		switcher++;
	break;
	case 6:
	//blue 0 0 255
	rect.setFillColor(Color(r,g,b));	
	r+=speed;
	if (r >= 134)
		switcher++;
	break;
	case 7:
	//purple 139 0 255
	rect.setFillColor(Color(r,g,b));	
	if (r <= 250)
		r+=speed;
	if (b >= 5)
		b-=speed;
	if (r>=250 and b <= 5)
		switcher++;
	break;
	}
}
