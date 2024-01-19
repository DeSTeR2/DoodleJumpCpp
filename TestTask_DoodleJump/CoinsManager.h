#pragma once

#include "Coins.h"

class CoinsManager {
	int coinNumber;
	double speed = 0.4;
	Player& player;
	Coins coins[100];
	int destroyCoinY;
	int windowWidth, windowHeight;
	int targetY = 0;

	void moveDown(int amount) {

		for (int i = 0; i < coinNumber; i++) {
			coins[i].setPosition(coins[i].x, coins[i].y + amount);
		}
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->moveDown(int(3 * speed));
	}

	void createNew(int i) {
		int x, y;
		x = rand() % (windowWidth - 100) + 40;
		y = rand() % windowHeight;
		coins[i].setPosition(x, y * (-1));
	}

public: 
	CoinsManager();
	CoinsManager(Player& player, int coinNumber, int windowWidth, int windowHeight): player(player), windowWidth(windowWidth), windowHeight(windowHeight), coinNumber(coinNumber){
		for (int i = 0; i < coinNumber;i++) {
			createNew(i);
		}
	}

	void draw() {
		for (int i = 0; i < coinNumber; i++) {
			coins[i].draw();

			if (coins[i].isCollide(player)) {
				player.coins++;
				createNew(i);
			}
			else 
			if (coins[i].y - 10 > windowHeight) {
				createNew(i);
			}

		}
	}

	void move(GamePlatforms& gamePlatforms) {
		moveToTarget();
		if (gamePlatforms.isMoving) {
			targetY = gamePlatforms.targetY;
		}
	}
};