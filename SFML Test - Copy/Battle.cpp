#include "UI Sprite.cpp"
#include "Time.cpp"
#include "Render Logic.cpp"
#include "Battle Enemy.cpp"
#include "Battle Player.cpp"
#include "XControl.cpp"
#include "Battle Menu.cpp"
#include "symbol.cpp"
#include "Battle Player Animation.cpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <Xinput.h>
#pragma once



// a = attack, b = heal, c = status change





using namespace std;
using namespace std::chrono; // nanoseconds, system_clock, seconds

class battle {
	battlePlayer* player1;
	battlePlayerAnim* pAnim;

	battleEnemy* currentlyActing;

	battleMenu* menu;

	string currentEnemyDecision;
	bool enemyActionDone;

	list<battleEnemy*> enemies;
	list<battleEnemy*>::iterator enemyIt;
	list<UISprite*> playerSprites;
	list<UISprite*> enemySprites;
	//list<UISprite*> menuSprites;
	list<UISprite*>::iterator enemySpriteIt;
	Texture* playerSheet;
	//UISprite* menu;
	Texture* menuT;
	UISprite* arrow;
	Texture* arrowT;
	Text attack;
	Font font;
	Texture* attBarT;
	UISprite* attBar;
	Texture* attSymbT;
	UISprite* attSymb;
	int selection;
	bool select = false;
	bool won = false;

	bool attacking = false;
	bool blocking = false;
	
	bool end = false;

	public:battle(list<battlePlayer*> charaList, Texture* sheet, list<battleEnemy*> enemies1) {
		selection = 1;
		
		playerSheet = sheet;
		this->player1 = *charaList.begin();

		pAnim = new battlePlayerAnim(player1->getSprite());

		this->enemies = enemies1;
	
		int yPos = 200;
		for (battleEnemy* enemy : this->enemies) {
			enemy->getSprite()->setCameraPosition(Vector2f(1000, yPos));
			yPos = yPos + 100;
		}
		player1->getSprite()->setCameraPosition(Vector2f(100, 200));

		/*menuT = new Texture();
		menuT->loadFromFile("Assets\\Battle Menu.png");
		menu = new UISprite("Background", menuT, Vector2i(0, 0), Vector2i(1800, 200), Vector2f(100, 700), Vector2f(1, 1));

		arrowT = new Texture();
		arrowT->loadFromFile("Assets\\arrow.jpg");
		arrow = new UISprite("menu", arrowT, Vector2i(0, 0), Vector2i(346, 208), Vector2f(180, 765), Vector2f(0.3, 0.3));

		attBarT = new Texture();
		attBarT->loadFromFile("Assets\\Att Bar.png");
		attBar = new UISprite("menu", attBarT, Vector2i(0, 0), Vector2i(1706, 200), Vector2f(100, 700), Vector2f(0.9, 0.9));

		attSymbT = new Texture();
		attSymbT->loadFromFile("Assets\\Att Symbol.png");

		formatOption(&attack, &font);
		attack.setString("Attack");
		attack.setPosition(Vector2f(300, 775));*/

		




//returnMenu();
	}

	public: battle() {

	}

public:
	bool fight(renderer* instance, double targetRate, pController* p1) {
		playerSprites = { player1->getSprite() };

		menu = new battleMenu(Vector2f(100, 700), instance, player1, &enemies, true);

		//list<Text*> textList{ &attack };


		bool run = true;
		timer* time = new timer();
		steady_clock::time_point start;
		steady_clock::time_point* startP;
		camera* cam = new camera();
		int p1Act = 0;
		list<battleEnemy*>::iterator p1Attacked;

		while (instance->getWindow()->isOpen() && run) {
			start = time->timerStart();
			startP = &start;
			Event event;
			while (instance->getWindow()->pollEvent(event))
			{
				if (event.type == Event::Closed)
					instance->getWindow()->close();
			}

			list<UIHitbox*> hitboxes = menu->getHitboxes();
			for (UIHitbox* hit : hitboxes) {
				hit->updatePos();
			}

			if (end) {
				instance->getWindow()->close();
			}


			instance->getWindow()->clear();

			enemySprites.clear();
			for (battleEnemy* enemy : enemies) {
				UISprite* s = enemy->getSprite();
				enemySprites.push_back(s);
			}
			instance->UIDisplay(enemySprites);
			instance->UIDisplay(playerSprites);
			instance->UIDisplay(menu->displayMenu());
			instance->UIDisplay(menu->displaySymbols());
			instance->textDisplay(menu->displayText());
			instance->UIDisplay(list<UISprite*>{menu->getPStats()->displySprite()});
			instance->textDisplay(menu->getPStats()->displayText());
			instance->hitboxDisplay(hitboxes);
			if (menu->isLocked()) {
				instance->UIDisplay(list<UISprite*>{menu->getPause()});
			}
			instance->getWindow()->display();

			checkBlocking(p1);


			checkPlayers();

			

			



			time->frameLimiter(targetRate, startP);
			float* delta = new float(time->checkTimer(startP));
			*delta = *delta / 1000000000;
			//controllerOption(p1);

			checkPAnim();


			menu->eachFrame(p1, delta);
			enemyActions(delta);
			checkEnemy();
			if (menu->finishedAction()) {
				p1Act = menu->getAct();
				p1Attacked = menu->getAttackedEnemy();
				if (p1Act == 0) {
					pAttackP(player1, *p1Attacked, menu->getPercent());
				}
			}

			if (won) {
				run = false;
			}

		}
		if (won) {
			return true;
		}
		return false;
	}

	void checkPAnim() {
		if (menu->isActing()) {
			pAnim->checkAtt(menu->getNextAnim());
		}
		else {
			pAnim->reset();
		}
		
	}


	void checkBlocking(pController* p) {
		if (p->checkL()) {
			blocking = true;
		}
		else {
			blocking = false;
		}
	}

	void enemyActions(float* deltaT) {
		
		if (currentlyActing != NULL) {
			if (!enemyActionDone) {
				if (currentlyActing->attackAnim(deltaT)) {
					enemyActionDone = true;
					

					int modifier = 0;
					if (currentEnemyDecision == "a") {
						battlePlayer* victim = currentlyActing->victim(list<battlePlayer*>{player1});
						modifier = currentlyActing->offAct();
						enemyAttack(victim, modifier);
					}

				}
			}
			else {
				currentlyActing->attackAnim(deltaT);
				if (currentlyActing->isAnimFinished()) {
					currentlyActing->resetAnimation();
					
					currentlyActing->resetTimer();
					currentlyActing = NULL;
					enemyActionDone = false;
				}
			}
		}
		else {
			for (battleEnemy* enemy : enemies) {
				if (enemy->isAttacking(deltaT)) {
					currentlyActing = enemy;
					currentEnemyDecision = currentlyActing->decideAct();
				}
			}
		}
	}

	void enemyAttack(battlePlayer* p, int att) {
		p->getHurtP(att, blocking);
		cout << p->getHP();
		if (p->getHP() <= 0){
			p->setDead(true);
		}
	}
	
	void checkPlayers() {
		if (player1->getDead()) {
			end = true;
		}
	}

	void checkEnemy() {
		
		list<battleEnemy*>::iterator i = enemies.begin();
		list<list<battleEnemy*>::iterator> iList;

		for (battleEnemy* enemy : enemies) {
			if (enemy->getHP() <= 0) {
				//delete menu;
				iList.push_back(i);
			}
			next(i);
		}

		for (list<battleEnemy*>::iterator i : iList) {
			
			//this->enemySprites.erase(enemySpriteIt);
			enemies.erase(i);
			if (enemies.empty()) {
				won = true;
				break;
			}
		}
	}

	void pAttackP(battlePlayer* p, battleEnemy* e, float percent) {
		int att = p->attack();
		att = att * (percent / 100);
		if (att == 0) {
			att = 1;
		}
		e->getHurtP(att);

		cout << e->getHP();

	}



};