#include "object hitbox.cpp"
#include "Overworld Enemy.cpp"
#pragma once

class enemyHitbox {
	objectHitbox* hitbox;
	overworldEnemy* enemy;

public:
	enemyHitbox(IntRect rect, bool b, overworldEnemy* en) {
		hitbox = new objectHitbox(rect, b, en->getSprite());
		enemy = en;
	}

	list<battleEnemy*> getEnemies() {
		return enemy->getEnemies();
	}

	objectHitbox* getHitbox() {
		return hitbox;
	}
	overworldEnemy* getEnemy() {
		return enemy;
	}
};