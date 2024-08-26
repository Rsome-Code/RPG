#include "movable UI.cpp"
#include "Animate.cpp"
#include "Symbol.cpp"
#include "UI Hitbox.cpp"
#pragma once

class attackBar {

	Vector2f position;
	list<UIHitbox*> hitboxes;
	list<symbol*> symbols;
	list<symbol*>::iterator symbLogic;
	list<animation*> hits;
	list<animation*> misses;
	Texture* attBarT;
	UISprite* attBar;
	UIHitbox* attackTarget;
	Texture* attSymbT;

	bool lastOffScreen;
	bool firstTime = true;
	float percentage = 0;
	float eachPercent = 0;
	float nextSymbol;
	float timeKeep;
	//The next symbols to be deleted
	list<list<symbol*>::iterator> toDelete;
	//How long the symbol delete anim should take
	float nextDelete;
	//How long left until the current symbol has to be deleted
	float untilDelete;
	//The timing for the current attack in seconds
	list<float> currentSetup;

	bool finishedAct;


public:
	attackBar(Vector2f pos) {

		position = pos;

		attBarT = new Texture();
		attBarT->loadFromFile("Assets\\Att Bar.png");
		attBar = new UISprite("menu", attBarT, Vector2i(0, 0), Vector2i(1706, 200), Vector2f(position.x + 210, position.y + 10), Vector2f(0.8, 0.9));
		attSymbT = new Texture();
		attSymbT->loadFromFile("Assets\\Att Symbol.png");
		nextDelete = 0.2;
		untilDelete = nextDelete;
		attackTarget = new UIHitbox(IntRect(Vector2i(20, 33), Vector2i(202, 172)), true, attBar);
	}

	bool getFinishedAct() {
		return finishedAct;
	}

	void setFinishedAct(bool set) {
		finishedAct = set;
	}
	


	float getPercent() {
		float temp = percentage;
		percentage = 0;
		return temp;
	}

	list<float> getSetup() {
		return currentSetup;
	}

	list<list<symbol*>::iterator> getToDelete() {
		return toDelete;
	}

	void createSetup(list<float> set) {
		currentSetup = set;
	}

	bool getLastOffScreen() {
		return lastOffScreen;
	}
	void setLastOffScreen(bool set) {
		lastOffScreen = set;
	}

	void actionCommand() {

		//Hitboxes are immediately deleted upon a-press
		if (!hitboxes.empty()) {

			bool collided = checkCollision();

			if (collided) {
				percentage = percentage + eachPercent;
			}

			animateSymbol(collided);

			list<symbol*>::iterator temp = symbols.begin();

			list<list<symbol*>::iterator>::iterator temp1 = toDelete.begin();

			if (!toDelete.empty()) {
				//temp1++;

				while (temp1 != toDelete.end()) {
					temp++;
					temp1++;
				}
			}
			toDelete.push_back(temp);
			lastOffScreen = false;

		}
		else if (!currentSetup.empty()) {
			currentSetup.erase(currentSetup.begin());
			lastOffScreen = true;
			
		}
		if (hitboxes.empty() && currentSetup.empty()) {
			finishedAct = true;
		}
		

	}

	void deleteSymbol(float* deltaT) {

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

	}

	int symbolsLeft() {
		int total = symbols.size() + currentSetup.size();
		return total;
	}

	list<UIHitbox*> getHitboxes() {
		list<UIHitbox*> temp = hitboxes;
		temp.push_front(attackTarget);
		return temp;
	}

	bool checkCollision() {

		UIHitbox* box = *hitboxes.begin();
		hitboxes.erase(hitboxes.begin());

		if (attackTarget->getCameraPos().x > box->getCameraPos().x + box->getSize().x) {

			delete(box);
			return false;
		}
		else if (attackTarget->getCameraPos().x + attackTarget->getSize().x < box->getCameraPos().x) {
			delete(box);
			return false;
		}
		else if (attackTarget->getCameraPos().y > box->getCameraPos().y + box->getSize().y) {
			delete(box);
			return false;
		}
		else if (attackTarget->getCameraPos().y + attackTarget->getSize().y < box->getCameraPos().y) {
			delete(box);
			return false;
		}

		else {
			delete(box);
			return true;
		}

	}

	void setEachPercent() {
		eachPercent = 100 / currentSetup.size();
	}

	UISprite* attackBarSetup() {
		return attBar;
	}

	list<symbol*> getSymbols() {
		return symbols;
	}

	void startSymbol() {
		symbol* temp = new symbol(position, attSymbT);
		symbols.push_back(temp);

		UIHitbox* tempHit = new UIHitbox(IntRect(Vector2i(15, 30), Vector2i(121, 176)), false, temp);
		hitboxes.push_back(tempHit);
		hits.push_back(new animation({ IntRect(Vector2i(197, 0), Vector2i(170, 200)), IntRect(Vector2i(380, 0), Vector2i(170, 200)) }, temp));

	}


	void animateSymbol(bool hit) {
		animation* anim = *hits.begin();
		anim->nextFrame(false);

		if (!hit) {
			anim->nextFrame(false);
		}

		delete (anim);
		hits.erase(hits.begin());

	}

	void symbolSetup(float* deltaT) {
		//Each timing is in relation to the last symbol
		//In seconds
		if (firstTime) {
			nextSymbol = *currentSetup.begin();
			firstTime = false;
		}
		timeKeep = timeKeep + *deltaT;
		if (timeKeep >= nextSymbol) {
			currentSetup.erase(currentSetup.begin());
			startSymbol();
			firstTime = true;
			timeKeep = 0;
		}

	}

	void moveSymbol(float* deltaT) {
		for (movableUI* symb : symbols) {
			symb->move(180, deltaT, 100);
		}
	}
};