#pragma once

#include "Platform.h"
#include "DropPlatform.h"


class GamePlatforms {
private: 
	int platformNumber;
	int spawnPlatormY, destroyPlatformY;
	int windowWidth, windowHeigth;

	int targetPosition = 500;

	int last = 0;
	
	Platform* lastAdded;
public: 
	Platform platforms[1000];
	
	GamePlatforms(int platformNumber, int spawnPlatormY, int destroyPlatformY,int windowWidth, int windowHeigth) : lastAdded(&platforms[0]) {
		//srand(time(0));
		
		this->platformNumber = platformNumber;
		this->windowWidth = windowWidth;
		this->windowHeigth = windowHeigth;

		int pref = spawnPlatormY;
		for (int i = 0; i < platformNumber; i++) {
			pref = rand() % 30 + 20;
			
			if (i==0) platforms[i].setPosition(rand() % windowWidth, windowHeigth - 30);
			else platforms[i].setPosition(rand() % windowWidth, platforms[i-1].y - pref);
			
			platforms[i].createType();
			last = i;
		}


		this->spawnPlatormY = spawnPlatormY;
		this->destroyPlatformY = destroyPlatformY;
	}

private: 

	void createNewPlatform(Platform& platform, int i) {
		int add = rand() % 25 + 20;
		platform.setPosition(rand() % 500, spawnPlatormY);
		platform.createType();
		last = i;

	}

	void moveUp(int amount) {
		for (int i = 0; i < platformNumber; i++) {
			platforms[i].setPosition(platforms[i].x, platforms[i].y - amount);
		}
	}

	void moveDown(int amount) {
		for (int i = 0; i < platformNumber; i++) {
			platforms[i].setPosition(platforms[i].x, platforms[i].y + amount);
		}
	}

public: 

	void draw() {
		for (int i = 0; i < platformNumber; i++) {
			if (platforms[i].y >= destroyPlatformY) createNewPlatform(platforms[i], i);
			platforms[i].draw();
		}
	}

	void move(Player& player) {

		Player pl = player;
		pl.move(0, -3);

		for (int i = 0; i < platformNumber; i++) {

			if (platforms[i].isCollide(player) && !platforms[i].isCollide(pl)) {
				if (platforms[i].y < targetPosition) moveDown(5);
				else player.dirY = 0;
				return;
			}
		}
		if (player.targetY >=0) player.dirY = 1;
	}

};