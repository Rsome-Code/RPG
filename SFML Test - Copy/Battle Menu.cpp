#include "UI Sprite.cpp"
#include "Xcontrol.cpp"
#include "Render Logic.cpp"
#include "movable UI.cpp"
#include "Animate.cpp"
#include "Symbol.cpp"
#include "Battle Player.cpp"
#include "Battle Enemy.cpp"
#include "Attack Bar.cpp"
#include "Player Stats-Battle.cpp"
#pragma once

class battleMenu {

	attackBar* attBar;

	bool active;

	Vector2f position;

	battlePlayer* player;
	list<battleEnemy*>* enemies;
	list<battleEnemy*>::iterator enemySelect;
	bool firstSelect = true;
	bool selecting = false;

	bool nextAnim = false;


	bool resetMenu = false;

	bool finishedAct = false;

	float percentage = 0;


	bool lock = false;

	list<UISprite*> display;
	list<symbol*> symbols;
	list<symbol*>::iterator symbLogic;
	list<animation*> hits;
	list<animation*> misses;

	bool lastOffScreen = false;
	float delay = 0.5;

	list<UIHitbox*> hitboxes;
	list<text*> displayT;
	UISprite* boarder;
	UISprite* arrow;
	text* option1;
	renderer* instance;

	Texture* menuT;

	Texture* arrowT;

	Texture* pauseT;
	UISprite* pause;

	statBox* pStats;



	//Texture* attBarT;
	//UISprite* attBar;
	UIHitbox* attackTarget;
	Texture* attSymbT;
	int selection;
	bool duringAct;
	bool setup;

	bool firstTime = true;
	float nextSymbol;

	bool APressed;
	bool leftPressed = false;
	bool rightPressed = false;
	bool upPressed = false;
	bool downPressed = false;

	//The next symbols to be deleted
	list<list<symbol*>::iterator> toDelete;
	//How long the symbol delete anim should take
	float nextDelete;
	//How long left until the current symbol has to be deleted
	float untilDelete;
	//The timing for the current attack in seconds
	list<float> currentSetup;


public:
	battleMenu(Vector2f pos, renderer* inst, battlePlayer* player, list<battleEnemy*>* enemies, bool active) {
		this->active = active;
		position = pos;
		this->player = player;
		this->enemies = enemies;
		instance = inst;
		menuT = new Texture();
		menuT->loadFromFile("Assets\\Battle Menu.png");
		boarder = new UISprite("Background", menuT, Vector2i(0, 0), Vector2i(1800, 200), position, Vector2f(1, 1));

		arrowT = new Texture();
		arrowT->loadFromFile("Assets\\arrow.jpg");
		arrow = new UISprite("menu", arrowT, Vector2i(0, 0), Vector2i(346, 208), Vector2f(position.x + 250, position.y + 76), Vector2f(0.3, 0.3));




		attSymbT = new Texture();
		attSymbT->loadFromFile("Assets\\Att Symbol.png");
		selection = 0;
		duringAct = false;

		Font* font = new Font();

		if (!font->loadFromFile("Assets\\FOT-PopJoyStd-B.otf")) {
			cout << "ERORR";
		}
		pStats = new statBox(player, position, font);
		option1 = new text("Attack", Vector2f(position.x + 400, position.y + 76), 30, font, &Color::White);


		

		display = { boarder, arrow};
		displayT = { option1 };
		
		setup = false;
		nextDelete = 0.2;
		untilDelete = nextDelete;
		enemySelect = enemies->begin();

		////////////////////////////////////////////////////////
		pauseT = new Texture();
		pauseT->loadFromFile("Assets\\Pause.png");
		pause = new UISprite("UI", pauseT, Vector2i(0, 0), Vector2i(512, 512), Vector2f(position.x + 650, position.y - 20), Vector2f(0.5, 0.5));
		///////////////////////////////////////////////////////
		attBar = new attackBar(position);
	}

public:

	void eachFrame(pController* p, float* deltaT) {
		pStats->updateStats();

		if (selecting) {
			enemySelection(p);
		}

		else if (duringAct) {
			
			lockConditions(p);

			if (!lock) {

				if (!setup) {
					this->choice();
				}
				if (!attBar->getSetup().empty()) {
					symbolSetup(deltaT);
				}
				moveSymbol(deltaT);

				actionCommand(p);
				if (!attBar->getToDelete().empty()) {
					attBar->deleteSymbol(deltaT);
				}
				if (attBar->getSymbols().empty() && attBar->getSetup().empty()) {

					resetMenu = true;
					//finishedAct = true;
				}
			}
		}
		else {
			if (active) {
				checkMenu(p);
			}
			
		}

		if (resetMenu) {
			//setup = false;
			returnMenu(deltaT);
			resetMenu = false;
		}

		
	}
	statBox* getPStats() {
		return pStats;
	}

	bool finishedAction() {
		if (attBar->getFinishedAct() && !lock) {
			
			attBar->setFinishedAct(false);
			setup = false;
			currentSetup.clear();

			return true;
		}
		return false;
	}

	void lockConditions(pController* p) {
		if (p->checkL()) {
			lock = true;
		}
		else {
			lock = false;
		}
	}

	int getAct() {
		return selection;
	}

	bool isLocked() {
		return lock;
	}

	bool isActing() {
		return duringAct;
	}

	float getPercent() {
		return attBar->getPercent();
	}

	UISprite* getPause() {
		return pause;
	}



	list<battleEnemy*>::iterator getAttackedEnemy() {
		return enemySelect;
	}


	////////////////////////////////////////////////////////////////////////////
	/*void deleteSymbol(pController* p, float* deltaT) {
		
		list <list<symbol*>::iterator> temp;
		symbol* symb;

		for (list<symbol*>::iterator i : toDelete) {
			symb = *i;
			if (symb->destroy(deltaT)) {
				temp.push_back(i);
			}
			
		}
		for (list<symbol*>::iterator j : temp) {
			//delete(*j);
			symbols.erase(symbols.begin());
			toDelete.erase(toDelete.begin());
		}
		temp.clear();

	}*/

	void choice(){

		if (selection == 0) {
			attackP();
		}
		attBar->setEachPercent();
	}



	list<UISprite*> displayMenu() {
		return display;
	}


	int symbolsLeft() {
		return attBar->symbolsLeft();
	}


	list<UISprite*> displaySymbols() {
		list<UISprite*> temp;
		for (UISprite* symb : attBar->getSymbols()) {
			temp.push_front(symb);
		}
		return temp;
	}


	list<text*> displayText() {
		return displayT;
	}


	list<UIHitbox*> getHitboxes() {
		return attBar->getHitboxes();
	}


	void checkMenu(pController* p) {
		if (p->checkA() && duringAct == false && APressed == false) {
			APressed = true;
			if (selection == 0) {

				selecting = true;
			}

		}
		else if (!p->checkA()) {
			APressed = false;
		}
	}

	

	void enemySelection(pController* p) {
		if (firstSelect) {
			enemySelect = enemies->begin();
			firstSelect = false;
		}
		battleEnemy* en = *enemySelect;
		Vector2f temp = en->getSprite()->getCameraPosition();
		temp = Vector2f(temp.x - 100, temp.y);

		arrow->setCameraPosition(temp);

		if (p->checkLEFT() && !leftPressed) {
			leftPressed = true;
			if (enemySelect == enemies->begin()) {
				enemySelect = enemies->end();
			}
			enemySelect = prev(enemySelect);
		}
		
		else if (p->checkRIGHT() && !rightPressed) {
			rightPressed = true;
			enemySelect = next(enemySelect);
			if (enemySelect == enemies->end()) {
				enemySelect = enemies->begin();
			}
		}
		
		else if (p->checkA()&& APressed==false) {
			APressed = true;
			duringAct = true;
			selecting = false;
			firstSelect = true;
		}
		else if (p->checkB()) {
			selecting = false;
			resetMenu = true;
			firstSelect = true;
		}
		if (!p->checkA()) {
			APressed = false;
		}
		if (!p->checkLEFT()) {
			leftPressed = false;
		}
		if (!p->checkRIGHT()) {
			rightPressed = false;
		}
	}

	void attackP() {
		attackBarSetup();
		attBar->createSetup({ 0, 2, 0.5 });
		setup = true;
	}

	void returnMenu(float* deltaT) {

		if (attBar->getLastOffScreen()) {
			delay = delay - *deltaT;
			lock = true;
			if (delay <= 0) {
				attBar->setLastOffScreen(false);
				lock = false;
				delay = 0.5;
			}
		}
		if (attBar->getLastOffScreen() == false) {
			
			display.erase(prev(display.end()));
			displayT.push_back(option1);
			display.push_back(arrow);
			arrow->setCameraPosition(Vector2f(position.x + 50, position.y + 76));
			duringAct = false;
		}
	}



	bool getNextAnim(){
		if (nextAnim) {
			nextAnim = false;
			return true;
		}
		return false;
	}




	//The following is for the attack bar
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void actionCommand(pController* p) {
		if (p->checkA() && APressed == false) {
			APressed = true;
			nextAnim = true;
			attBar->actionCommand();
		}
		else if (!p->checkA()) {
			APressed = false;
		}
	}


	bool checkCollision() {
		attBar->checkCollision();
	}

	void attackBarSetup() {
		displayT.clear();
		display.erase(prev(display.end()));
		display.push_back(attBar->attackBarSetup());
	}

	void startSymbol() {
		attBar->startSymbol();
	}


	void animateSymbol(bool hit) {
		attBar->animateSymbol(hit);
		
	}

	void symbolSetup(float* deltaT) {
		attBar->symbolSetup(deltaT);

	}

	void moveSymbol(float* deltaT) {
		attBar->moveSymbol(deltaT);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	

	void formatOption(Text* text, Font* font) {
		text->setFont(*font);
		text->setCharacterSize(30); // in pixels
		text->setFillColor(sf::Color::White); // set the text color
		text->setStyle(sf::Text::Bold | sf::Text::Regular); // set text style
	}
};