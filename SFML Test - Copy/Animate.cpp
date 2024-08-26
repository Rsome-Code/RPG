//This stores the rectangles in a sprite sheet to be used for the stored sprite.
//This will not determine timing, only the frames themselves.
//The animation must be present on the spritesheet loaded into the sprite being animated.

#include <SFML/Graphics.hpp>
#include "Object Sprite.cpp"
#include <list>
using namespace std;
using namespace sf;
#pragma once

class animation {
	UISprite* sprite;
	list<IntRect> frameIndexes;
	//bool repeat;
	list<IntRect>::iterator current;
	int size;

public: 
	animation(list<IntRect> indexes, UISprite* sprite) {
	this->frameIndexes = indexes;
	this->sprite = sprite;
	//this->repeat = repeat;
	this->current = frameIndexes.begin();
	size = indexes.size();
	}

public:animation() {
		cout << "AY";
	}

public:
	void setFrame(IntRect rect) {
		sprite->applyRect(rect);
	}

	bool nextFrame(bool loop) {
	if (current == frameIndexes.end()) {
		if (loop) {
			reset(loop);
			this->setFrame(*current);
			this->current++;
		}
		return true;
	}
	else {
		this->setFrame(*current);
		this->current++;
		return false;
	}
}

	bool isFinished() {
		if (current == next(frameIndexes.begin())) {
			return true;
		}
		return false;
	}

public:void reset(bool loop) {
	current = frameIndexes.begin();
	//nextFrame(loop);
}
};