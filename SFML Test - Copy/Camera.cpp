//This class contains information related to the camera

#include "Object Sprite.cpp"
#pragma once

class camera {
	Vector2f position;
	objectSprite* following;
	Vector2f offset; //This will allow the object the camera is following to be uncentered if you wish
	float fAmount;

public:camera() {
		position = Vector2f(0, 0);
	}
public:camera(objectSprite* following, Vector2f offset) {
		this->position = Vector2f(0, 0);
		this->following = following;
		this->offset = offset;
		fAmount = getFAmount();
	}
public:camera(objectSprite* following) {
	this->position = Vector2f(0, 0);
	this->following = following;
	this->offset = Vector2f(-960, -540);
	fAmount = getFAmount();
}


	void follow() {
		position = following->getPosition();
	}
	Vector2f getPosition() {
		return this->position + this->offset;
	}
	Vector2f getOffset() {
		return this->offset;
	}
	public: void setOffset(Vector2f off) {
		offset = off;
	}


//The following relates to when the object the camera is following is flipped horizontally.

public:bool checkFlip(){
	return following->getFlipped();
}

public: objectSprite* getFollowing() {
	return following;
}
public: int getFlipInc() {
	return following->getRectX();
}
public:float getFAmount() {
	return following->getFAmount();
}
public:void flipCamera() {
	if (following->getFlipped()){
		this->position = Vector2f(position.x + fAmount, position.y);
	}
	else {
		this->position = Vector2f(position.x - fAmount, position.y);
	}

}
};