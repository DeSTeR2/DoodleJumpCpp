#pragma once

#include "Platform.h"
#include "DropPlatform.h"
#include "ScoreManager.h"

class GamePlatforms {
private: 
	int platformNumber;
	int spawnPlatormY, destroyPlatformY;
	int windowWidth, windowHeigth;
	int score = 0, passedPlatforms = 0;
	int targetPosition = windowHeigth - windowHeigth*0.2;
	int last = 0, lastCollide = 0;
	float speed = 0.4;
	
	int theLowestPlatform = 0;


public: 
	bool isMoving = false;
	Platform platforms[1000];
	int targetY = 0;
	
	GamePlatforms();

	GamePlatforms(int platformNumber, int spawnPlatormY, int destroyPlatformY,int windowWidth, int windowHeigth){
		//srand(time(0));
		
		this->platformNumber = platformNumber;
		this->windowWidth = windowWidth;
		this->windowHeigth = windowHeigth;

		for (int i = 0; i < platformNumber; i++) {
			int add = rand() % 30;
			
			if (i == 0) { 
				platforms[i].setPosition(windowWidth / 2, windowHeigth - 30); 
				platforms[i].createType("normal");
			}
			else {
				platforms[i].setPosition(rand() % windowWidth, platforms[i - 1].y - add);
				platforms[i].createType();
			}
			
			last = i;
		}


		this->spawnPlatormY = spawnPlatormY;
		this->destroyPlatformY = destroyPlatformY;
		targetPosition = windowHeigth - windowHeigth * 0.2;
	}

private: 

	void createNewPlatform(Platform& platform, int i) {
		int add = rand() % 30;

		int posY = platforms[last].y;

		platform.setPosition(rand() % windowWidth, posY - add);
		platform.createType();
		last = i;

	}

	void moveUp(int amount) {
		for (int i = 0; i < platformNumber; i++) {
			platforms[i].setPosition(platforms[i].x, platforms[i].y - amount);
		}
	}

	void moveDown(int amount) {
		score += amount;
		
		for (int i = 0; i < platformNumber; i++) {
			platforms[i].setPosition(platforms[i].x, platforms[i].y + amount);
		}
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->moveDown(3 * speed);
	}

public: 

	void draw() {
		for (int i = 0; i < platformNumber; i++) {
			if (platforms[i].y >= destroyPlatformY) createNewPlatform(platforms[i], i);
			platforms[i].draw();
		}
	}

	void move(Player& player) {


		moveToTarget();
		if (targetY == 0) isMoving = false;
		else isMoving = true;

		Player pl = player;
		pl.move(0, -3);
		//cout << "Score: " << score << endl << "Passed platforms: " << passedPlatforms << endl << endl;
		for (int i = 0; i < platformNumber; i++) {

			if (platforms[i].isCollide(player) && !platforms[i].isCollide(pl)) {

				if (platforms[i].y < targetPosition) { 
					if (i != lastCollide) passedPlatforms++;

					lastCollide = i;
					//player.dirY = 0;
					if (player.targetY ==0 ) targetY = targetPosition - platforms[i].y;
				}
				else {
					player.setLowestPlatform({ platforms[i].x, platforms[i].y });
					player.dirY = 0;
				}
				return;
			}
		}
		if (player.targetY >=0) player.dirY = 1;
	}


	int getScore() {
		return score;
	}
	int getPassedPlatforms() {
		return passedPlatforms;
	}
};