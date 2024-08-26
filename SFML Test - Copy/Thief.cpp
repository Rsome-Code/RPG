#include "Battle Enemy.cpp"
#include "UI Sprite.cpp"
#include "Animate.cpp"
#include <list>
#pragma once

class thief:public battleEnemy {

public:
	thief(Texture* enemySheet) {
		hp = 10;
		maxHP = hp;
		mp = 5;
		maxMP = mp;
		att = 10;
		def = 2;
		spirit = 2;
		speed = 5;
		sprite = new UISprite("enemy", enemySheet, Vector2i(392, 23), Vector2i(31, 31), Vector2f(0, 0), Vector2f(3, 3));
		animation* attAnim = new animation(list<IntRect> {IntRect(Vector2i(127, 71), Vector2i(74, 37)), IntRect(Vector2i(45, 39), Vector2i(57, 69)), IntRect(Vector2i(111, 128), Vector2i(63, 53))}, sprite);
		animations = { { {attAnim, new animTimer(attAnim, 1, true)} } };


	}

	string decideAct() {
		decision = 0;
		targetFrame = 3;
		i = animations.begin();
		return "a";
	}

	battlePlayer* victim(list<battlePlayer*> players) {
		return *players.begin();
	}

	int offAct() {
		if (decision == 0) {
			return attack();
		}
		return 0;
	}



	int attack() {
		return att / 2;
	}
	





};