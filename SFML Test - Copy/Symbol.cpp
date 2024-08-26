#include"Movable UI.cpp"
#pragma once
class symbol: public movableUI {
	using movableUI::movableUI;

	float destroyTime;
	float since = 0;


public:
	symbol(Vector2f position, Texture* texture) {

		this->texture = texture;
		this->type = "menu";
		loadTexture();
		setRect(Vector2i(0, 0), Vector2i(172, 200));
		setScale(Vector2f(1, 0.9));
		setCameraPosition(Vector2f(position.x + 1700, position.y + 10));
		destroyTime = 0.5;
	}

	bool destroy(float* deltaT) {
		since = since + *deltaT;
		if (since >= destroyTime) {
			//delete(this);
			return true;
		}
		return false;
	}


};