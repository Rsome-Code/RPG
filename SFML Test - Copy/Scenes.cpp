
#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <Xinput.h>
#include "Time.cpp"
#include "Animate.cpp"
#include "Texture.cpp"
#include "Object Sprite.cpp"
#include "Player Sprite.cpp"
#include "Render Logic.cpp"
#include "Enemy Hitbox.cpp"
#include "Camera.cpp"
#include "Animation Timer.cpp"
//#include "Controller.cpp"
#include "XControl.cpp"
#include "Overworld Controls.cpp"
#include "Overworld Enemy.cpp"
#include "Object Hitbox.cpp"
#include "UI Hitbox.cpp"
#include "Overworld Player Animation.cpp"
#include "Battle.cpp"
#include "thief.cpp"
#pragma once
using namespace std;
using namespace std::chrono; // nanoseconds, system_clock, seconds




class area {
	//playable* pBattle = new playable(sheet, Vector2i(377, 5), Vector2i(16, 24), Vector2f(1000, 500), Vector2f(5.f, 5.f), 1);
	playable* player;
	
	
	list<objectHitbox*> hitList;
	list<enemyHitbox*> eHitList;
	list<overworldEnemy*> enemyList;
	list<objectSprite*>::iterator enemyIterator;

public: area(Texture* sheet) {
	player = new playable("player", sheet, Vector2i(377, 159), Vector2i(16, 16), Vector2f(1000, 500), Vector2f(5.f, 5.f), 1);
}

	public: void firstArea(renderer* instance, double targetRate, pController* p1,  overworldControls* over, battlePlayer* chara1, Texture* sheet) {
		//TController* controller = new TController(0);

		list<battlePlayer*> charaList = { chara1 };

		//////////////////////////////////////////////////////////
		//The following should be deleted when the loop ends:

		//These assets should be loaded from something else, json maybe?


		Texture* enemySheet = new Texture();
		enemySheet->loadFromFile("Assets\\Enemy sheet.png");
		overworldEnemy* first = new overworldEnemy("enemy", enemySheet, Vector2i(392, 23), Vector2i(31, 31), Vector2f(1200, 500), Vector2f(3, 3), 1);
		first->setEnemies(list<battleEnemy*>{ new thief(enemySheet)});
		overworldEnemy* second = new overworldEnemy("enemy", enemySheet, Vector2i(392, 23), Vector2i(31, 31), Vector2f(1400, 500), Vector2f(3, 3), 1);
		second->setEnemies(list<battleEnemy*>{ new thief(enemySheet), new thief(enemySheet)});
		enemyHitbox* eHitbox = new enemyHitbox(IntRect(Vector2i(0, 0), Vector2i(31, 31)), true, first);
		enemyHitbox* eHitbox1 = new enemyHitbox(IntRect(Vector2i(0, 0), Vector2i(31, 31)), true, second);
		Texture* grid = new Texture();
		grid->loadFromFile("Assets\\grids.png");
		objectSprite* background = new objectSprite("background", grid, Vector2i(0, 0), Vector2i(4905, 4747), Vector2f(0, 0), Vector2f(0.5f, 0.5f), 1);

		camera* cam = new camera(player->getSprite());

		


		list<UISprite*> spriteList{};
		list<objectSprite*> objectList{ background, player->getSprite()};
		enemyList = { first, second};

		list<UIHitbox*> uList{ player->getHitbox(), eHitbox->getHitbox()};
		hitList = { player->getHitbox(), eHitbox->getHitbox(), eHitbox1->getHitbox()};
		eHitList = { eHitbox, eHitbox1 };
		list<overworldEnemy*> enemyCollided;




		bool run = true;
		Vector2f position;
		timer* time = new timer();
		steady_clock::time_point start;
		steady_clock::time_point* startP;
		string pCollide = "none";
		start = time->timerStart();
		startP = &start;
		float deltaT = 0;

		while (instance->getWindow()->isOpen() && run) {
			
			Event event;
			while (instance->getWindow()->pollEvent(event))
			{
				if (event.type == Event::Closed)
					instance->getWindow()->close();
			}

			cam->follow();
		
			for (objectHitbox* box : hitList) {
				box->updatePos();
			}

			enemyCollided = checkEnemyCollision(player->getHitbox());

			enemyCollideActions(enemyCollided, charaList, sheet, instance, targetRate, p1);


			instance->getWindow()->clear();
			instance->objectDisplay(objectList, cam);
			for (overworldEnemy* e : enemyList) {
				instance->objectDisplay(list<objectSprite*> {e->getSprite()}, cam);
			}
			
			instance->objectHitboxSetup(hitList, cam);
			instance->hitboxDisplay(uList);
			instance->getWindow()->display();


			



			over->controllerActions(player, p1, &deltaT);
		
			time->frameLimiter(targetRate, startP);
			deltaT= time->checkTimer(startP);
			deltaT = deltaT / 1000000000;
			start = time->timerStart();
			startP = &start;

			
		}
	}








	void enemyCollideActions(list<overworldEnemy*> enemyCollided, list<battlePlayer*> charaList, Texture* sheet, renderer* instance, float targetRate, pController* p1) {
		if (!enemyCollided.empty()) {
			for (overworldEnemy* collide : enemyCollided) {

				battle* scenario = new battle(charaList, sheet, collide->getEnemies());
				if (scenario->fight(instance, targetRate, p1)) {
					delete collide;
				}
			}
		}
	}

	public:list<overworldEnemy*> checkEnemyCollision(objectHitbox* pHitbox) {
		list<overworldEnemy*> overworldEnemyList;
		list<list<enemyHitbox*>::iterator> iList;
		list<list<overworldEnemy*>::iterator> jList;
		list<enemyHitbox*>::iterator i = eHitList.begin();

		list<overworldEnemy*>::iterator j = enemyList.begin();
		

		
		for (enemyHitbox* box : eHitList) {
			if (pHitbox->getPosition().x > box->getHitbox()->getPosition().x + box->getHitbox()->getSize().x) {

			}
			else if (pHitbox->getPosition().x + pHitbox->getSize().x < box->getHitbox()->getPosition().x) {

			}
			else if (pHitbox->getPosition().y > box->getHitbox()->getPosition().y + box->getHitbox()->getSize().y) {

			}
			else if (pHitbox->getPosition().y + pHitbox->getSize().y < box->getHitbox()->getPosition().y) {

			}
			
			else {


				overworldEnemyList.push_back(box->getEnemy());
				iList.push_back(i);
				jList.push_back(j);
					
					
				
			}

			next(i);
			next(j);
	

		}
		
		for (list<enemyHitbox*>::iterator i : iList) {
			eHitList.erase(i);
		}
		for (list<overworldEnemy*>::iterator j : jList) {
			enemyList.erase(j);
		}
		return overworldEnemyList;
	}
};