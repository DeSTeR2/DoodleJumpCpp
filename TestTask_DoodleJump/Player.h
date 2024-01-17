#pragma once

#include "BallFire.h"
#include "Framework.h"
#pragma comment(lib, "FrameworkRelease_x64.lib")

#define ff first
#define ss second

class Player {
private:
	Sprite* sprite[3];
	int curSprite=2;
	double speed = 0.7;

public: 
	double targetY = 0;
	int width, height;
	double posX, posY,dirX=0,dirY=1;

	Player() {
		sprite[0] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-left.png");
		sprite[1] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-puca-odskok.png");
		sprite[2] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-right-odskok.png");
		getSpriteSize(sprite[0], width, height);
	}
	Player(double x, double y) {
		sprite[0] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-left.png");
		sprite[1] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-puca-odskok.png");
		sprite[2] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-right-odskok.png");
		getSpriteSize(sprite[0], width, height);
		posX = x;
		posY = y;
	}

	void draw() {
		curSprite %= 3;
		drawSprite(sprite[curSprite], posX, posY);
	}

	void move() {
		if (dirX > 0) curSprite = 2;
		if (dirX == 0)curSprite = 1;
		if (dirX < 0) curSprite = 0;

		if (targetY > 0) moveToTarget();
		if (dirY == 0) jump();
		//if (dirY != 0) targetY = 0;

		getSpriteSize(sprite[curSprite], width, height);
		this->setPosition(this->posX + dirX* speed, this->posY + dirY* speed);
	}

	void move(double dirX, double dirY) {
		if (dirX > 0) curSprite = 2;
		if (dirX == 0) curSprite = 1;
		if (dirX < 0) curSprite = 0;
		getSpriteSize(sprite[curSprite], width, height);
		this->setPosition(this->posX + dirX* speed, this->posY + dirY* speed);
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->setPosition(this->posX + dirX* speed, this->posY - 3* speed);
	}

	void jump() {
		if (targetY == 0)
			targetY = 100;
		moveToTarget();
	}

	void setPosition(double x, double y) {
		posX = x;
		posY = y;
	}

};