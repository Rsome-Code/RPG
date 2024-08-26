#include "Movable UI.cpp"
#pragma once

class battlePlayer {
	int hp;
	int maxHP;
	int mp;
	int maxMP;
	int att;
	int def;
	int spirit;
	bool dead;
	movableUI* sprite;

public:battlePlayer(int hp, int maxHP, int mp, int maxMP, int att, int def, int spirit, movableUI* sprite) {
		this->maxHP = maxHP;
		this->maxMP = maxMP;
		this->hp = 9999;
		this->mp = mp;
		this->att = 999;
		this->def = def;
		this->spirit = spirit;
		this->sprite = sprite;
	}

public: 
	void getHurtP(int damage, bool blocking) {
		damage = damage - (def / 4);
		if (blocking) {
			damage = damage / 2;
		}
		this->hp = this->hp - damage;
		}

	int getHP() {
		return hp;
	}

	void setDead(bool d) {
		dead = d;
	}
	bool getDead() {
		return dead;
	}

	public: void getHurtM(int damage) {
		damage = damage - (spirit / 4);
		this->hp = this->hp - damage;
	}

	public: void heal(int heal) {
		this->hp = this->hp + heal;
	}

	public: int attack() {
		return this->att / 2;
	}
	movableUI* getSprite() {
		return sprite;
	}

	int getMP() {
		return mp;
	}
};