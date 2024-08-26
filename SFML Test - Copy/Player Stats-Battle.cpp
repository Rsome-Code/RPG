#include "Battle Player.cpp"
#include "Text.cpp"
#pragma once
class statBox {

	battlePlayer* player;
	Vector2f position;
	Texture* pStatsT;
	UISprite* pStats;
	text* pName;
	text* hp;
	text* hpNum;
	text* mp;
	text* mpNum;

public:
	statBox(battlePlayer* p, Vector2f pos, Font* font) {
		player = p;
		position = pos;

		pStatsT = new Texture();
		pStatsT->loadFromFile("Assets\\Player Stats.png");
		pStats = new UISprite("menu", pStatsT, Vector2i(0, 0), Vector2i(216, 200), position, Vector2f(1, 1));

		pName = new text("Tercom", Vector2f(position.x +10, position.y + 10), 30, font, &Color::White);
		hp = new text("HP", Vector2f(position.x + 10, position.y + 40), 30, font, &Color::White);
		mp = new text("MP", Vector2f(position.x + 10, position.y + 70), 30, font, &Color::White);
		hpNum = new text(player->getHP(), Vector2f(position.x + 90, position.y + 40), 30, font, &Color::White);
		mpNum = new text(player->getHP(), Vector2f(position.x + 90, position.y + 70), 30, font, &Color::White);
	}

	void updateStats() {
		hpNum->setContent(player->getHP());
		mpNum->setContent(player->getMP());
	}

	UISprite* displySprite() {
		return pStats;
	}
	list<text*> displayText() {
		return list<text*> {pName, hp, mp, hpNum, mpNum};
	}
};