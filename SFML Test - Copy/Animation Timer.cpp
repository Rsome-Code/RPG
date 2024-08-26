//This class will control the timing for the animation assigned to it.
//It can animate at any fps you want, regardless of the game's fps, though it cannot exceed it.
//Multiple of these can be applied to one set of animation frames

#include "Animate.cpp"
#pragma once

class animTimer {
	animation* anim;
	float fps;
	float targetDelta;
	float countDown;
	bool loop;

public:animTimer(animation* anim, float fps, bool loop) {
		this->anim = anim;
		this->fps = fps;
		targetDelta = (1 / fps);
		countDown = targetDelta;
		this->loop = loop;
	}


public: 
	bool run(float* delta) {
		bool nextFrame = false;
		if (*delta >= countDown) {
			nextFrame = true;
			anim->nextFrame(loop);
			countDown = targetDelta;
		}
		else {
			countDown = countDown - *delta;
			
		}
		return nextFrame;
		
	}

	bool isFinished() {
		return anim->isFinished();
	}

	void skip() {
		countDown = 0;
	}
	void reset() {
		countDown = targetDelta;
	}
};