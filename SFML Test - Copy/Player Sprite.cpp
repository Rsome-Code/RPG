
#include <iostream>
#include "Object Sprite.cpp"
#include "Movable Object.cpp"
#include "Battle Player.cpp"
#include "Overworld Player Animation.cpp"
#include "Object Hitbox.cpp"
#pragma once

class playable {

	movable* sprite;
	overworldPlayerAnim* pAnim;
	objectHitbox* pHitbox;

public:
	playable(string type, Texture* texture, Vector2i rect, Vector2i rectSize, Vector2f position, Vector2f scale, int cameraSpeed) {
		sprite = new movable(type, texture, rect, rectSize, position, scale, cameraSpeed);
		pAnim = new overworldPlayerAnim(sprite);
		pHitbox = new objectHitbox(IntRect(Vector2i(0, 0), Vector2i(16, 16)), true, sprite);
	}

public:Vector2f stickMove(Vector2f lStick, float* since) {
	float last = *since;
	
	float thisFrameD = last * sprite->getSpeed();

	float dLower = -thisFrameD;
	float stickUpper = 32767;
	float stickLower = -32768;

	float stickTotal = stickUpper + -(stickLower);
	float dTotal = thisFrameD * 2;

	float x = lStick.x + -(stickLower);
	float percentX = x / stickTotal;
	float distX = (dTotal * percentX) -(-dLower);

	float y = lStick.y + -(stickLower);
	float percentY = y / stickTotal;
	float distY = (dTotal * percentY) - (-dLower);

	Vector2f newPos = Vector2f(sprite->getPosition().x + distX, sprite->getPosition().y - distY);
	sprite->setPosition(newPos);

	return Vector2f(distX, distY);

}

	  movable* getSprite() {
		  return sprite;
	  }

	  overworldPlayerAnim* getAnim() {
		  return pAnim;
	  }
	  objectHitbox* getHitbox() {
		  return pHitbox;
	  }
};