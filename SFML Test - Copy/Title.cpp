#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <windows.h>
#include "XControl.cpp"
#include "UI Sprite.cpp"
#include "Render Logic.cpp"
#include "Time.cpp"
#include "Text.cpp"
using namespace sf;
using namespace std;
using namespace std::chrono; // nanoseconds, system_clock, seconds

class mainMenu {

	int select = 0;

public:void menu(renderer* instance, double targetRate, pController* p1) {

	Font* font = new Font();
	if (!font->loadFromFile("Assets\\FOT-PopJoyStd-B.otf")) {
		cout << "ERORR";
	}

	text* title = new text("Title", Vector2f(800, 100), 72, font, &Color::White);

	bool run = true;

	text* option1 = new text("Start", Vector2f(600, 500), 32, font, &Color::White);
	int temp = 5;
	text* option2 = new text("Exit", Vector2f(600, 600), 32, font, &Color::White);


	Texture* arrowT = new Texture();
	arrowT->loadFromFile("Assets\\arrow.jpg");

	UISprite* arrow = new UISprite("menu", arrowT, Vector2i(0, 0), Vector2i(346, 208), Vector2f(170, 400), Vector2f(1, 1));
	list<UISprite*> sprites = { arrow };



	list<text*> textList{ title, option1, option2};



	camera* cam = new camera();

	timer* time = new timer();
	steady_clock::time_point start;
	steady_clock::time_point* startP = &start;

	while (instance->getWindow()->isOpen() && run) {
		start = time->timerStart();
		startP = &start;
		Event event;
		while (instance->getWindow()->pollEvent(event))
		{
			if (event.type == Event::Closed)
				instance->getWindow()->close();
		}

		instance->getWindow()->clear();
		instance->textDisplay(textList);
		instance->UIDisplay(sprites);
		instance->getWindow()->display();
		time->frameLimiter(targetRate, startP);

		if (p1->checkA()) {
			run = false;
			PlaySound(TEXT("Assets\\SFX\\Selecting Right.wav"), NULL, SND_ASYNC);
		}
		if (p1->checkDOWN()) {
			changeSelect(1);
			arrow->setCameraPosition(Vector2f(170, 500));
		}
		else if(p1->checkUP()) {
			changeSelect(0);
			arrow->setCameraPosition(Vector2f(170, 400));
		}

	}



	delete time;
	//delete(startP);


	delete(cam);


	if (this->select == 1) {
		instance->getWindow()->close();
	}
	
}

	  void changeSelect(int num) {
		  if (num != select) {
			  select = num;
			  PlaySound(TEXT("Assets\\SFX\\Select Cursor.wav"), NULL, SND_ASYNC);
		  }
	  }
};