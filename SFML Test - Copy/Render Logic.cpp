/*This entire class' responsibility is to handly the render logic.
Essentially, it interpret's the current state of the game to figure out exactly what it should show the player.*/

#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <windows.h>
#include <list>
#include "Object Sprite.cpp"
#include "Camera.cpp"
#include "UI Sprite.cpp"
#include "UI Hitbox.cpp"
#include "Object Hitbox.cpp"
#include "text.cpp"
#include <iostream>

#pragma once
using namespace sf;
using namespace std;


class renderer{

	RenderWindow* w;
	float ratio;

public: 
	renderer(RenderWindow* wi) {
		this->w = wi;
		ratio = getRatio();

	}


public:
	void textDisplay(list<text*> textList){
		//list<text*> temp = resolutionTextScale(textList);
		for (text* text : textList) {
			w->draw(*text->getRender());
		}
	}


	void objectDisplay(list<objectSprite*> objectList, camera* cam) {
		 //This check if the sprite the camera is following has been flipped
		//resolutionObjectScale(objectList);
		bool flipped = cam->checkFlip();

		//This number is how much the camera needs to be moved if said sprite is flipped
		float flipAmount = cam->getFAmount();
		Vector2f cPosition = cam->getPosition();
		for (objectSprite* sprite : objectList) {


			//These lines check to see where on the game screen the object is displayed, if at all
			Vector2f sPosition = sprite->getPosition();
			  
			Vector2f newPos = sPosition - cPosition;
			sprite->setCameraPosition(newPos, flipAmount);

			Sprite* s = sprite->getSprite();

			w->draw(*s);
		}
	}
	void UIDisplay(list<UISprite*> spriteList) {
		//resolutionScale(spriteList);
		for (UISprite* sprite : spriteList) {

			//These lines check to see where on the game screen the object is displayed, if at all
			string id = typeid(objectSprite).name();

			Sprite* s = sprite->getSprite();

			w->draw(*s);
		}
	}
	void hitboxDisplay(list<UIHitbox*> hitList) {


		for (UIHitbox* hit : hitList) {
			if (hit->isVisible()) {
				sf::RectangleShape rectangle(Vector2f(hit->getSize().x * ratio, hit->getSize().y * ratio));
				rectangle.setPosition(hit->getCameraPos());
				rectangle.setFillColor(sf::Color(0, 255, 0, 128));
				w->draw(rectangle);
			}
		}
	}
	void objectHitboxSetup(list<objectHitbox*> hitList, camera* cam) {

		Vector2f camPosition = cam->getPosition();
		for (objectHitbox* hit : hitList) {
			Vector2f newCam = cam->getPosition();
			hit->setCameraPos(hit->getPosition() - camPosition);
		}
	}





	float getRatio() {
		float currentRes = w->getSize().y;
		return currentRes / 1080;
	}

	/*void resolutionObjectScale(list<objectSprite*> sprites) {
		list<UISprite*> temp;
		for (UISprite* s : sprites) {
			temp.push_back(s);
		}
		resolutionScale(temp);
	}

	void resolutionScale(list<UISprite*> sprites) {
		
		for (UISprite* sprite : sprites) {
			Vector2f currentS = sprite->getScale();
			Sprite* s = sprite->getSprite();
			
			s->setScale((Vector2f(currentS.x * ratio, currentS.y * ratio)));
		}
	}

	list<text*> resolutionTextScale(list<text*> texts) {
		list<text*> temp;
		for (text* t : texts) {
			temp.push_back(t);
			float currentS = t->getSize();
			t->setRenderSize(currentS);
		}
	}*/

	RenderWindow* getWindow() {
		return w;
	}
};
