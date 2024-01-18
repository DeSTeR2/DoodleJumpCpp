#pragma once

#include "Player.h"

class Coins {
	
	Sprite* sprite;
	//Player* player;
	int width, height;

	void reSize(Sprite& sprite, float spriteMulti) {
		int wid, hei;
		getSpriteSize(&sprite, wid, hei);
		setSpriteSize(&sprite, wid * spriteMulti, hei * spriteMulti);
		//getSpriteSize(&sprite, width, height);
	}

	bool isCollideWithDot(double posX, double posY) {
		if (this->x <= posX && this->x + this->width >= posX
			&& this->y <= posY && this->y + this->height >= posY) return true;
		return false;
	}

	bool isCollideWithLine(pair<double, double> a, pair<double, double> b) {
		if (this->x <= a.ff && this->x + this->width >= a.ff && this->x <= b.ff && this->x + this->width >= b.ff)
			if (this->y >= a.ss && this->y + this->height >= a.ss && this->y <= b.ss && this->y + this->height <= b.ss)
				return true;

		return false;
	}

public:
	int x = 20, y = 20;
	Coins() {
		sprite = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\coin.png");
		reSize(*sprite, 0.05);
		getSpriteSize(sprite, width, height);
		//cout << "CoinCreated\n";

	}

	bool isCollide(Player& player) {

		if (isCollideWithDot(player.posX, player.posY) || isCollideWithDot(player.posX + player.width, player.posY)
			|| isCollideWithDot(player.posX, player.posY + player.height) || isCollideWithDot(player.posX + player.width, player.posY + player.height))
		{
			return true;
		}

		pair<double, double> first = { player.posX, player.posY };
		pair<double, double> second = { player.posX + player.width, player.posY };
		pair<double, double> third = { player.posX, player.posY + player.height };
		pair<double, double> forth = { player.posX + player.width, player.posY + player.height };

		if (isCollideWithLine(first, third) || isCollideWithLine(second, forth)) {
			return true;
		}

		return false;
	}
	
	void draw() {
		drawSprite(sprite, x, y);
	}

	void setPosition(int x,int y) {
		this->x = x;
		this->y = y; 
	}
};