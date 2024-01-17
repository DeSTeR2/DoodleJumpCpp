#pragma once
#include "Framework.h"
#include "Player.h"
#pragma comment(lib, "FrameworkRelease_x64.lib")

#define ff first
#define ss second

class Platform
{
private:
	int width, height;
	const char* normal = "D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\game-platform.png";
	const char* drop = "D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\fall-platform1.png";

	string type;
	int dropChanse = 10;
public: 
	Sprite* platform;
	int x=-10, y=0;
	
	Platform() {
		createType();
	}

	Platform(int x, int y) {
		this->x = x;
		this -> y = y;
		
		createType();
	}

private: 
	bool isCollideWithDot(int posX, int posY) {
		if (this->x <= posX && this->x + this->width >= posX
			&& this->y <= posY && this->y + this->height >= posY) return true;
		return false;
	}

	bool isCollideWithLine(pair<int, int> a, pair<int,int> b) {
		if (this->x <= a.ff && this->x + this->width >= a.ff && this->x <= b.ff && this->x + this->width >= b.ff)
			if (this->y >= a.ss && this->y + this->height >= a.ss && this->y <= b.ss && this->y + this->height <= b.ss)
				return true;

		return false;
	}

public: 

	void createType() {
		
		if (rand() % 100 <= dropChanse) {
			platform = createSprite(drop); type = "drop";
		}
		else {
			platform = createSprite(normal);
			type = "normal";
		}
		getSpriteSize(platform, width, height);
		setSpriteSize(platform, width * 0.8, height * 0.8);
		getSpriteSize(platform, width, height);
	}

	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool isCollide(Player& player) {
		if (isCollideWithDot(player.posX, player.posY) || isCollideWithDot(player.posX + player.width, player.posY)
			|| isCollideWithDot(player.posX, player.posY + player.height) || isCollideWithDot(player.posX + player.width, player.posY + player.height))
			return true;
		
		pair<int, int> first = { player.posX, player.posY };
		pair<int, int> second = { player.posX + player.width, player.posY };
		pair<int, int> third = { player.posX, player.posY + player.height };
		pair<int, int> forth = { player.posX + player.width, player.posY + player.height };

		if (isCollideWithLine(first, third) || isCollideWithLine(second, forth)) return true;

		return false;
	}

	void draw() {
		drawSprite(platform, x, y);
	}

};

