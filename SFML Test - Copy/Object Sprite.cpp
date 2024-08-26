#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <iterator>
#include "UI Sprite.cpp"


#pragma once


using namespace std;
using namespace sf;



class objectSprite:public UISprite{
	using UISprite::UISprite;
	//textureControl textureList[64];


protected:Vector2f position;
		 list<objectSprite*>::iterator objectI;

	int cameraSpeed;
	bool flipped = false;
	bool flipPos = false;
	
	public: objectSprite(string type, Texture* texture, Vector2i rect, Vector2i rectSize, Vector2f position, Vector2f scale, int cameraSpeed) {
		this->type = type;
		this->texture = texture;
		this->cameraSpeed = cameraSpeed;
		loadTexture();
		setRect(rect, rectSize);
		setPosition(position);
		setScale(scale);
		cameraPosition = Vector2f(0, 0);
	}
	public: objectSprite() {
		cout << "huh?";
		this->cameraSpeed = 1;

	}


public: void setPosition(Vector2f position) {
		this->position = position;
	}

	void setCameraPosition(Vector2f c, float fAmount) {
		if (flipPos) {
			c = Vector2f(c.x + (fAmount), c.y);
		}
		this->cameraPosition = c;
		thisOne.setPosition(c);
	}


public: Vector2f getPosition() {
		return position;
	}



public:void flip() {
	if (!flipped) {
		setScale(Vector2f(-this->scale.x, this->scale.y));
		this->setPosition(Vector2f(this->position.x + (this->rectSize.x * -this->scale.x), this->position.y));
		flipped = true;
		
	}
	else {
		setScale(Vector2f(-this->scale.x, this->scale.y));
		this->setPosition(Vector2f (this->position.x - (this->rectSize.x * this->scale.x), this->position.y));
		flipped = false;
		
	}
}
public:void setFlipPos(bool f) {
	flipPos = f;
}
public:float getFAmount() {
	return this->rectSize.x * -this->scale.x;
}
public:bool getFlipped() {
	return flipped;
}
public:void setFlipped(bool flip) {
	this->flipped = flip;
}
public:int getRectX() {
	return rectSize.x;
}


};