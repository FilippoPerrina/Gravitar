#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screens.h"
#include "Spaceship.h"
using namespace std;
using namespace sf;


int main(){
	std::vector<Screen*> Screens;
	int screen = 0;
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(600, 600), "Gravitar", Style::Default, settings);
	window.setKeyRepeatEnabled(false);
	Spaceship ship;
	ship.setposition(window.getSize().x/2,window.getSize().y/2);
	Menu menu;
	Screens.push_back(&menu);
	SolarSystem solarsystem;
	solarsystem.setShip(ship);
	Screens.push_back(&solarsystem);
	Game game;
	game.setShip(ship);
	Screens.push_back(&game);

	while (screen >= 0){
		if(screen == 2) menu.setreturnint(screen);
		else if(screen == 1) menu.setreturnint(screen);
		screen = Screens[screen]->Run(window);
	}

}

