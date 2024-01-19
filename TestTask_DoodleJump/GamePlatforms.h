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
	int targetPosition = int(windowHeigth - windowHeigth*0.2);
	int last = 0, lastCollide = 0;
	double speed = 0.4;
	vector<Platform> additionalPlatforms;
	int theLowestPlatform = 0;


public: 
	bool isMoving = false;
	vector<Platform> platforms;
	int targetY = 0;
	
	GamePlatforms();

	GamePlatforms(int platformNumber, int spawnPlatormY, int destroyPlatformY,int windowWidth, int windowHeigth, Player player){
		//srand(time(0));
		platforms.resize(platformNumber);
		this->platformNumber = platformNumber;
		this->windowWidth = windowWidth;
		this->windowHeigth = windowHeigth;

		for (int i = 0; i < platformNumber; i++) {
			int add = rand() % 30;
			
			if (i == 0) { 
				platforms[i].setPosition(player.posX, player.posY + player.height); 
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
		targetPosition = int(player.posY * 1.2);

		//setPlatformsOnPlayer(player);
	}

private: 

	void createNewPlatform(Platform& platform, int i) {
		int add = rand() % 30;

		int posY = int(platforms[last].y);

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
		for (int i = 0; i < additionalPlatforms.size(); i++) {
			additionalPlatforms[i].setPosition(additionalPlatforms[i].x, additionalPlatforms[i].y + amount);
		}
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->moveDown(int(3 * speed));
	}

public: 

	vector<Platform>& getPlatforms() {
		return platforms;
	}

	//void setPlatformsOnPlayer(Player& player) {
	//	player.platforms = platforms;
	//}

	void addPlatform(Platform plat) {
		additionalPlatforms.push_back(plat);
	}

	void draw() {
		for (int i = 0; i < platformNumber; i++) {
			if (platforms[i].y >= destroyPlatformY) createNewPlatform(platforms[i], i);
			platforms[i].draw();
		}
		vector<Platform> newPlat;
		for (int i = 0; i < additionalPlatforms.size(); i++) {
			if (additionalPlatforms[i].y >= destroyPlatformY) {
				continue;
			}
			newPlat.push_back(additionalPlatforms[i]);
			additionalPlatforms[i].draw();
		}
		additionalPlatforms = newPlat;
	}

	void move(Player& player) {


		moveToTarget();
		if (targetY == 0) isMoving = false;
		else isMoving = true;

		Player pl = player;
		pl.move(0, -3);

		int lowestY = 0, lowestIndex=0;
		
		setLowestPlatformOnPlayer(player);
		
		//cout << "Score: " << score << endl << "Passed platforms: " << passedPlatforms << endl << endl;
		for (int i = 0; i < platformNumber; i++) {
			if (platforms[i].isCollide(player) && !platforms[i].isCollide(pl)) {

				if (platforms[i].kill()) continue;

				if (platforms[i].y < targetPosition) {

					if (i != lastCollide) passedPlatforms++;
					lastCollide = i;
					//player.dirY = 0;
					if (player.targetY == 0) targetY = int(targetPosition - platforms[i].y);
				}
				else {
					
					player.dirY = 0;
				}
				return;
			}
		}

		for (int i = 0; i < additionalPlatforms.size(); i++) {

			if (additionalPlatforms[i].isCollide(player) && !additionalPlatforms[i].isCollide(pl)) {
				if (additionalPlatforms[i].y < targetPosition) {

					if (i != lastCollide) passedPlatforms++;
					lastCollide = i;
					//player.dirY = 0;
					if (player.targetY == 0) targetY = int(targetPosition - additionalPlatforms[i].y);
				}
				else {
					player.setLowestPlatform({ additionalPlatforms[i].x, additionalPlatforms[i].y });
					player.dirY = 0;
				}
				return;
			}
		}
		if (player.targetY >=0) player.dirY = 1;
	}

	void setLowestPlatformOnPlayer(Player& player) {
		int lowestY = 0;
		for (int i = 0; i < platformNumber; i++) {

			if (platforms[i].y > lowestY && platforms[i].y < int(windowHeigth * 0.9) && platforms[i].getType() == "normal") {
				lowestY = int(platforms[i].y);
				player.setLowestPlatform({ platforms[i].x, platforms[i].y });
			}
		}
	}

	int getScore() {
		return score;
	}
	int getPassedPlatforms() {
		return passedPlatforms;
	}
};