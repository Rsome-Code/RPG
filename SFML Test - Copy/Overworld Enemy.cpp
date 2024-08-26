#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <list>
#include <iterator>
#include <Windows.h>
#include "Movable Object.cpp"
#include "Battle Enemy.cpp"

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

#pragma once
using namespace std;


class overworldEnemy {

	list<battleEnemy*> enemies;

	movable* sprite;
	

public: overworldEnemy(string type, Texture* texture, Vector2i rect, Vector2i rectSize, Vector2f position, Vector2f scale, int cameraSpeed) {

	sprite = new movable(type, texture, rect, rectSize, position, scale, cameraSpeed);
	
	//enemies = list<battleEnemy*>{ new thief(texture) };
}
public:
	list<battleEnemy*> getEnemies() {
		return enemies;
	}

	void setEnemies(list<battleEnemy*> list) {
		this->enemies = list;
	}
	movable* getSprite() {
		return sprite;
	}

};