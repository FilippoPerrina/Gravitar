#include "Game.h"

using namespace std;
using namespace sf;

Game::Game() {
	Spaceship ship;
	list<Bullet*> bullets;
	list<Bullet*>::iterator it;
}

int Game::Run(sf::RenderWindow &window){
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed){
				if(event.key.code == Keyboard::Escape) return 0;
			}
			ship.direction(event);
			ship.ifShooting(event);
		}
		ship.move();
		ship.shoot(bullets);
		window.clear();
		ship.draw(window);
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
		window.display();
	}
	return 0;
}

