#include "UI Sprite.cpp"
#include "Battle Player.cpp"
#include "Animate.cpp"
#include "Animation Timer.cpp"
#include <list>
#pragma once

//Abstract Class

class battleEnemy {
protected:
	int hp;
	int maxHP;
	int mp;
	int maxMP;
	int att;
	int def;
	int spirit;
	float speed;
	float untilAttack;
	int decision;
	UISprite* sprite;
	list<tuple<animation*, animTimer*>> animations;
	bool firstFrame = true;
	list<tuple<animation*, animTimer*>>::iterator i;

	int frameNum = 0;
	int targetFrame = 0;



public:
	UISprite* getSprite() {
		return sprite;
	}
public: 
	void getHurtP(int damage) {
	damage = damage - (def / 4);
	this->hp = this->hp - damage;
	}
	int getHP() {
		return this->hp;
	}

	void getHurtM(int damage) {
		damage = damage - (spirit / 4);
		hp = hp - damage;
	}

	bool isAttacking(float* deltaT) {
		untilAttack = untilAttack + *deltaT;
		if (untilAttack >= speed) {
			//untilAttack = 0;
			return true;
		}
		return false;
	}

	void resetTimer() {
		untilAttack = 0;
		firstFrame = true;
	}
	bool attackAnim(float* deltaT) {
		bool temp = false;
		if (get<1>(*i)->run(deltaT)) {
			frameNum = frameNum + 1;
			if (frameNum == targetFrame) {
				temp = true;
			}
		}
		return temp;
	}

	void resetAnimation() {
		sprite->setRect(Vector2i(392, 23), Vector2i(31, 31));
		get<0>(*i)->reset(false);
		get<1>(*i)->reset();
		frameNum = 0;
	}

	virtual string decideAct() = 0;

	virtual int offAct() = 0;

	virtual battlePlayer* victim(list<battlePlayer*> players) = 0;

	

	bool isAnimFinished() {
		if (get<1>(*i)->isFinished()) {
			return true;
		}
		return false;
	}
};