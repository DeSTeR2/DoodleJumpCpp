#pragma once
#include "Framework.h"
#include "Player.h"
#pragma comment(lib, "FrameworkRelease_x64.lib")

#define ff first
#define ss second

class Platform
{
private:
	double spriteSize = 0.6;

	int width, height;
	const char* normal = "D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\game-platform.png";
	const char* drop = "D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\fall-platform1.png";
	const char* dropAnimation[3] = {
		"D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\fall-platform2.png",
		"D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\fall-platform3.png",
		"D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\fall-platform4.png"
	};
	int dropAnimationStage = -1;
	int prefTime = 0;
	bool dead = false, toDraw = true;

	string type;
	int dropChanse = 10;
public: 
	Sprite* platform;
	double x=-10, y=0;
	
	Platform() {
		createType();
	}

	Platform(double x, double y) {
		this->x = x;
		this -> y = y;
		
		createType();
	}

private: 
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

	void createType() {
		
		dropAnimationStage = 0;
		dead = false;
		toDraw = true;
		if (rand() % 100 <= dropChanse) {
			platform = createSprite(drop); type = "drop";
		}
		else {
			platform = createSprite(normal);
			type = "normal";
		}
		getSpriteSize(platform, width, height);
		setSpriteSize(platform, width * spriteSize, height * spriteSize);
		getSpriteSize(platform, width, height);
	}

	void setPosition(double x, double y) {
		this->x = x;
		this->y = y;
	}

	bool isCollide(Player& player) {
		
		
		if (isCollideWithDot(player.posX, player.posY) || isCollideWithDot(player.posX + player.width, player.posY)
			|| isCollideWithDot(player.posX, player.posY + player.height) || isCollideWithDot(player.posX + player.width, player.posY + player.height))
		{
			if (type =="normal") return true;
			dead = true;
			return false;
		}
		
		pair<double, double> first = { player.posX, player.posY };
		pair<double, double> second = { player.posX + player.width, player.posY };
		pair<double, double> third = { player.posX, player.posY + player.height };
		pair<double, double> forth = { player.posX + player.width, player.posY + player.height };

		if (isCollideWithLine(first, third) || isCollideWithLine(second, forth)) {
			if (type == "normal") return true;
			dead = true;
			return false;
		}

		return false;
	}

	void deadAnimation(bool start) {
		if (!start) return;
		if (dropAnimationStage >= 2) {
			toDraw = false; setPosition(this->x, this->y+1);
			return;
		}
		if (getTickCount() - prefTime > 40) {
			dropAnimationStage++; 
			
			prefTime = getTickCount();
			platform = createSprite(dropAnimation[dropAnimationStage]);
			getSpriteSize(platform, width, height);
			setSpriteSize(platform, width * spriteSize, height * spriteSize);
			getSpriteSize(platform, width, height);
		
		}
	}

	void draw() {
		deadAnimation(dead);
		drawSprite(platform, x, y);
	}

};

