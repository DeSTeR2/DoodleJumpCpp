#pragma once

#include "BallFire.h"
//#include "Framework.h"
#include "Platform.h"
#include "GamePlatforms.h"
//#pragma comment(lib, "FrameworkRelease_x64.lib")

#define ff first
#define ss second

class Player {
private:
	Sprite* sprite[3];
	int curSprite = 2;
	double speed = 0.7;
	bool isKilled = false;
	
	float sprintBootAbility = 1, springBootCost = 20;
	int startSprintBootAbility = 0;
	//GamePlatforms& gamePlatforms;

public:
	//vector<Platform> &platforms;
	int health = 5;
	double targetY = 0;
	int width, height;
	double posX, posY, dirX = 0, dirY = 1;
	int windowWidth, windowHeight;
	int coins = 0;
	int passedPlatforms = 0;
	pair<int, int> lowestPlatform;


	Player(int windowWidth, int  windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) {
		sprite[0] = createSprite(".\\data\\blue-lik-left.png");
		sprite[1] = createSprite(".\\data\\blue-lik-puca-odskok.png");
		sprite[2] = createSprite(".\\data\\blue-lik-right-odskok.png");
		getSpriteSize(sprite[1], width, height);
		posX = windowWidth / 2;
		posY = windowHeight / 2;
	}
	/*Player(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) {
		sprite[0] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-left.png");
		sprite[1] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-puca-odskok.png");
		sprite[2] = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\blue-lik-right-odskok.png");
		getSpriteSize(sprite[0], width, height);
		posX = x;
		posY = y;
	}*/

	void draw() {
		//cout << "In player: " << lowestPlatform.ff << " " << lowestPlatform.ss << endl;
		curSprite %= 3;
		drawSprite(sprite[curSprite], int(posX), int(posY));
	}

	void reduseHealth() {
		health--;
		if (health <= 0) {
			this->posY += 10;
			killPlayer();
			return;
		}
		posY = windowHeight-1;
		targetY = windowHeight - lowestPlatform.ss + height;
		posX = lowestPlatform.ff;
	}

	void move() {
		if (dirX > 0) curSprite = 2;
		if (dirX == 0)curSprite = 1;
		if (dirX < 0) curSprite = 0;

		//passedPlatforms += curCollide == lastCollide;

		if ((getTickCount() - startSprintBootAbility) / 1000 >= 20) {
			sprintBootAbility = 1;
		}

		if ((this->posY+2 >= windowHeight)) {
			reduseHealth();
		}

		if (targetY > 0) moveToTarget();
		if (dirY == 0) jump();
		//if (dirY != 0) targetY = 0;

		//getSpriteSize(sprite[curSprite], width, height);
		this->setPosition(this->posX + dirX * speed, this->posY + (dirY) * 1);

		if (this->posX >= windowWidth) this->posX = 0;
		if (this->posX + this->width <= 0) this->posX = windowWidth - this->width;
	}

	void move(double dirX, double dirY) {
		if (dirX > 0) curSprite = 2;
		if (dirX == 0) curSprite = 1;
		if (dirX < 0) curSprite = 0;
		//getSpriteSize(sprite[curSprite], width, height);
		this->setPosition(this->posX + dirX * speed, this->posY + dirY * speed);
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->setPosition(this->posX + dirX * speed, this->posY - 3 * speed);
	}

	void jump() {
		if (targetY == 0)
			targetY = 120*sprintBootAbility;
		moveToTarget();
	}

	void setPosition(double x, double y) {
		posX = x;
		posY = y;
	}

	void setLowestPlatform(pair<int,int> position) {
		lowestPlatform = position;
	}

	void setSpringBoot() {
		if (coins >= springBootCost) {
			coins -= int(springBootCost);
			sprintBootAbility = 2.5;
			startSprintBootAbility = getTickCount();
		}
	}

	int getCoin() {
		return coins;
	}

	void killPlayer() {
		isKilled = true;
	}

	bool isDead() {
		return ((this->posY > windowHeight) || isKilled);
	}
};