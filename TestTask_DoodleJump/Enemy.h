#pragma once

#include "Platform.h"

class Enemy {
	Sprite* sprite;
	int platformX, platformY;
	string links[3] = {
		".\\sprites\\Enemy1.png",
		".\\sprites\\Enemy2.png",
		".\\sprites\\Enemy3.png"
	};
	bool killed = false;
	Platform platforms[2];

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
	int width, height;
	double x, y;


	Enemy() {
		//int index = rand() % 3;
		//const char* link = links[index].c_str();
		//sprite = createSprite(link);
		//getSpriteSize(sprite, width, height);
	}

	Enemy(GamePlatforms& gamePlatforms, int windowWidth, int windowHeight, double y){
		int index = rand() % 3;
		const char* link = links[index].c_str();
		sprite = createSprite(link);
		getSpriteSize(sprite, width, height);
		//int X, y;
		x = rand() % (windowWidth - width);

		this->y = y;
		//y = rand() % windowHeight;
		setPosition(x, y);
		killed = false;
		//cout << x << " " << y << endl;
		for (int i = 0; i < 2; i++) {
			platforms[i].createType("normal");
			gamePlatforms.addPlatform(platforms[i]);
		}
	}

	bool isCollide(BallFire& player) {


		if (isCollideWithDot(player.x, player.y) || isCollideWithDot(player.x + player.width, player.y)
			|| isCollideWithDot(player.x, player.y + player.height) || isCollideWithDot(player.x + player.width, player.y + player.height))
		{
			return true;
		}

		pair<double, double> first = { player.x, player.y };
		pair<double, double> second = { player.x + player.width, player.y };
		pair<double, double> third = { player.x, player.y + player.height };
		pair<double, double> forth = { player.x + player.width, player.y + player.height };

		if (isCollideWithLine(first, third) || isCollideWithLine(second, forth)) {
			return true;
		}

		return false;
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
		if (killed) return;
		drawSprite(sprite, int(x), int(y));
	}

	void kill() {
		killed = true;
	}

	bool isKilled() {
		return killed;
	}

	void setPosition(double x, double y) {
		this->x = x;
		this->y = y;


		platformX = int(x)-5;
		platformY = int(y) + this->height;

		for (int i = 0; i < 2; i++) {
			platforms[i].setPosition(platformX + i * (platforms[i].getWidth() + 10) , platformY);
		}
	}
};