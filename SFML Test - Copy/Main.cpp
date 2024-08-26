//#include "Time.cpp"
#include "Animate.cpp"
#include "Texture.cpp"
#include "Object Sprite.cpp"
#include "Render Logic.cpp"
#include "Overworld Controls.cpp"
#include <chrono>
#include <thread>
#include <iostream>
#include "SFML/Graphics.hpp"
#include <windows.h>
#include "Scenes.cpp"
#include <Xinput.h>
#include "Controller.cpp"
#include "XControl.cpp"
#include "Title.cpp"
#include "Battle Player.cpp"
#pragma once
#pragma comment(lib,"winmm.lib")

using namespace std;
using namespace std::chrono; // nanoseconds, system_clock, seconds

int main() {
	//Set the framerate here
	double targetFPS = 60;

	pController* p1 = new pController(0);
	RenderWindow window(VideoMode(1920, 1080), "Executable");

	RenderWindow* w = &window;
	renderer* instance = new renderer(w);
	Texture* sheet = new Texture();
	sheet->loadFromFile("Assets\\NES - Final Fantasy - Light Warriors.png");
	area first = area(sheet);
	overworldControls* over = new overworldControls();
	mainMenu* menu = new mainMenu();

	battlePlayer* chara1 = new battlePlayer(20, 20, 10, 10, 15, 0, 5, new movableUI("player1", sheet, Vector2i(377, 5), Vector2i(16, 24), Vector2f(100, 800), Vector2f(5, 5)));

	menu->menu(instance, targetFPS, p1);

	//cout << "hi";
	first.firstArea(instance, targetFPS, p1, over, chara1, sheet);
}