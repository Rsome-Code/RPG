#include "Animate.cpp"
#include "Animation Timer.cpp"
#include "Movable UI.cpp"
#pragma once

class battlePlayerAnim {
	animation* walkRightF;
	animation* standing;
	int currentFrame;

public:
	battlePlayerAnim(movableUI* player) {
		walkRightF = new animation(list<IntRect> {IntRect(360, 5, 16, 23), IntRect(233, 183, 16, 39), IntRect(174, 183, 32, 32) }, player);
		standing = new animation(list<IntRect> {IntRect(377, 5, 16, 24)}, player);
	}

	void reset() {
		walkRightF->reset(false);
		standing->nextFrame(true);
	}

	void nextAttFrame() {
		walkRightF->nextFrame(true);
	}

	void checkAtt(bool next) {
		if (next) {
			nextAttFrame();
		}
	}
};