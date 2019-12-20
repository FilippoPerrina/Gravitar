#include "Bunker.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>


#define PI 3.141592653589793


double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


Bunker::Bunker()
{
	isdraw = false;
	ratio = 1.0 / fRand(0.8, 2);
	for_shooting = seconds(fRand(0, ratio));
	rot = 0;
	directions = NULL;
	type = 0;
	directions = new double[3];
	bullets_speed = new double[3];
}


void Bunker::settype(int a)
{
	type = a;
	for (int i = 0; i < type; i++) {
		directions[i] = fRand(-(3.0 / 4 * PI), -(1.0 / 4 * PI));
		bullets_speed[i] = fRand(450, 750);
	}
}


void Bunker::rotate(double x)
{
	bunker.rotate(x);
	rot = x;
}


void Bunker::drawing()
{
	bunker.setFillColor(sf::Color::Blue);
	bunker.setOutlineColor(Color(0, 0, 50));
	bunker.setOutlineThickness(2);
	bunker.setPointCount(20);
	bunker.setOrigin(117.5, 154);
	bunker.setPoint(0, sf::Vector2f(100, 100));
	bunker.setPoint(1, sf::Vector2f(100, 125));
	bunker.setPoint(2, sf::Vector2f(105, 125));
	bunker.setPoint(3, sf::Vector2f(105, 154));
	bunker.setPoint(4, sf::Vector2f(130, 154));
	bunker.setPoint(5, sf::Vector2f(130, 125));
	bunker.setPoint(6, sf::Vector2f(135, 125));
	bunker.setPoint(7, sf::Vector2f(135, 100));
	bunker.setPoint(8, sf::Vector2f(130, 100));
	bunker.setPoint(9, sf::Vector2f(130, 105));
	bunker.setPoint(10, sf::Vector2f(125, 105));
	bunker.setPoint(11, sf::Vector2f(125, 100));
	bunker.setPoint(12, sf::Vector2f(120, 100));
	bunker.setPoint(13, sf::Vector2f(120, 105));
	bunker.setPoint(14, sf::Vector2f(115, 105));
	bunker.setPoint(15, sf::Vector2f(115, 100));
	bunker.setPoint(16, sf::Vector2f(110, 100));
	bunker.setPoint(17, sf::Vector2f(110, 105));
	bunker.setPoint(18, sf::Vector2f(105, 105));
	bunker.setPoint(19, sf::Vector2f(105, 100));
	isdraw = true;
}


void Bunker::position(int x, int y)
{
	bunker.setPosition(x,y);
}


void Bunker::draw(sf::RenderWindow& window)
{
	double x = bunker.getPosition().x, y = bunker.getPosition().y - 50;
	if (rot > 300) {
		x -= 22;
		y += 5;
	}
	else if (rot > 20) {
		x += 22;
		y += 5;
	}
	for_shooting += clock_canshoot.restart();
	if (for_shooting.asSeconds() >= ratio) {
		for (int i = 0; i < type; i++) {
			Bullet **tmp = new Bullet*;
			*tmp = new Bullet(x, y, directions[i], bullets_speed[i]);
			bullets.push_front(*tmp);
			for_shooting = clock_canshoot.restart();
		}
	}

	list<Bullet*>::iterator it;
	for(it = bullets.begin(); it != bullets.end(); ) {
		(*it)->move();
		if ((*it)->isAlive(window)) {
			(*it)->draw(window);
			it++;
		}
		else {
			delete *it;
			it = bullets.erase(it);
		}
	}

	window.draw(bunker);
}
