#include "Animate.cpp"
#include "Animation Timer.cpp"
#pragma once

class overworldPlayerAnim {
	animation* walkDownF;
	animation* walkUpF;
	animation* walkRightF;
	animation* walkLeftF;
	animTimer* Down;
	animTimer* Up;
	animTimer* Left;
	animTimer* Right;

public:
	overworldPlayerAnim(UISprite* player) {
		walkDownF = new animation(list<IntRect> {IntRect(187, 159, 16, 16), IntRect(377, 159, 16, 16)}, player);
		walkUpF = new animation(list<IntRect> {IntRect(360, 159, 16, 16), IntRect(204, 159, 16, 16)}, player);
		walkRightF = new animation(list<IntRect> {IntRect(343, 159, 16, 16), IntRect(326, 159, 16, 16)}, player);
		walkLeftF = new animation(list<IntRect> {IntRect(221, 159, 16, 16), IntRect(238, 159, 16, 16)}, player);
		Down = new animTimer(walkDownF, 4, true);
		Up = new animTimer(walkUpF, 4, true);
		Left = new animTimer(walkLeftF, 4, true);
		Right = new animTimer(walkRightF, 4, true);
	}
	overworldPlayerAnim(){}

public:
	void walkUp(float* deltaT) {
		Up->run(deltaT);
		Down->skip();
		Left->skip();
		Right->skip();
	}

	void walkDown(float* deltaT) {
		Down->run(deltaT);
		Up->skip();
		Left->skip();
		Right->skip();
	}
	void walkRight(float* deltaT) {
		Down->skip();
		Up->skip();
		Left->skip();
		Right->run(deltaT);
	}
	void walkLeft(float* deltaT) {
		Down->skip();
		Up->skip();
		Left->run(deltaT);
		Right->skip();
	}
	void noWalk() {
		Down->skip();
		Up->skip();
		Left->skip();
		Right->skip();
	}
};