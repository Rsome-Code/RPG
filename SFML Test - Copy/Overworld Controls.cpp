
#include "Animate.cpp"
#include "Texture.cpp"
#include "Object Sprite.cpp"
#include "Player Sprite.cpp"
#include "Render Logic.cpp"
#include "Camera.cpp"
#include "Animation Timer.cpp"
#include "XControl.cpp"
#include "Time.cpp"
#include "Overworld Player Animation.cpp"
#pragma once

class overworldControls {

public:
	void controllerActions(playable* p, pController* p1, float* deltaT) {

		movable* player = p->getSprite();
		overworldPlayerAnim* pAnim = p->getAnim();

		if (p1->checkX()) {
			player->setSpeed(1000);
		}
		else {
			player->setSpeed(500);
		}

		Vector2f lStick = p1->checkLSTICK();

		if (lStick.x == 0 && lStick.y == 0) {
			if (p1->checkRIGHT() && p1->checkUP()) {
				player->move(315, deltaT, 100);
				pAnim->walkUp(deltaT);
			}
			else if (p1->checkRIGHT() && p1->checkDOWN()) {
				player->move(45, deltaT, 100);
				pAnim->walkDown(deltaT);
			}
			else if (p1->checkLEFT() && p1->checkUP()) {
				player->move(225, deltaT, 100);
				pAnim->walkUp(deltaT);
			}
			else if (p1->checkLEFT() && p1->checkDOWN()) {
				player->move(135, deltaT, 100); 
				pAnim->walkDown(deltaT);
			}

			else if (p1->checkRIGHT()) {
				player->move(0, deltaT, 100);
				pAnim -> walkRight(deltaT);
			}
			else if (p1->checkUP()) {
				player->move(270, deltaT, 100);
				pAnim->walkUp(deltaT);
			}
			else if (p1->checkLEFT()) {
				player->move(180, deltaT, 100);
				pAnim->walkLeft(deltaT);
			}
			else if (p1->checkDOWN()) {
				player->move(90, deltaT, 100);
				pAnim->walkDown(deltaT);
			}
			else {
				pAnim->noWalk();
			}
		}

		else {
			Vector2f movement = p->stickMove(lStick, deltaT);
			float x = abs(movement.x);
			float y = abs(movement.y);
			if (x > y) {
				if (movement.x >= 0) {
					pAnim->walkRight(deltaT);
				}
				else {
					pAnim->walkLeft(deltaT);
				}
			}
			else {
				if (movement.y >= 0) {
					pAnim->walkUp(deltaT);
				}
				else {
					pAnim->walkDown(deltaT);
				}
			}
		}
	}
};