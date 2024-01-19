#pragma once

#include "Enemy.h"

class EnemyController {
	int EnemyNumber;
	int spawnY;
	int windowWidth, windowHeight;
	vector<Enemy> enemies;
	double speed = 0.337;
	int targetY = 0;

	void moveDown(double amount) {
		for (int i = 0; i < EnemyNumber; i++) {
			enemies[i].setPosition(enemies[i].x, enemies[i].y + amount);
		}
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->moveDown(3.0 * speed);
	}

	void createNew(int i, GamePlatforms& gamePlatforms) {
		int y = windowHeight * (i + 1) - rand() % int(windowHeight * 0.5);

		enemies[i] = Enemy(gamePlatforms, windowWidth, windowHeight,-y);
	}
public:
	EnemyController(int EnemyNumber, int spawnY, int windowWidth, int windowHeight, GamePlatforms& gamePlatforms) :
		EnemyNumber(EnemyNumber), spawnY(spawnY), windowWidth(windowWidth), windowHeight(windowHeight) {
		enemies.resize(EnemyNumber);
		for (int i = 0; i < EnemyNumber; i++) {
			createNew(i, gamePlatforms);
		}
	}

	void move(GamePlatforms& gamePlatforms) {
		moveToTarget();
		if (gamePlatforms.isMoving)
			targetY = gamePlatforms.targetY;

		for (int i = 0; i < EnemyNumber; i++) {
			if (enemies[i].y > windowHeight) createNew(i, gamePlatforms);
		}
	}

	void draw(BallController& balls, Player& player, GamePlatforms& gamePlatforms) {
		for (int i = 0; i < EnemyNumber; i++) {
				enemies[i].draw();
		}
		vector<BallFire>& ball = balls.getBalls();
		for (int i = 0; i < EnemyNumber; i++) {
			if (enemies[i].isKilled()) continue;

			if (enemies[i].isCollide(player)) {

				Player pl = player;
				pl.move(0, -3);
				if (!enemies[i].isCollide(pl)) {
					enemies[i].kill();
					continue;
				}

				gamePlatforms.setLowestPlatformOnPlayer(player);
				player.reduseHealth();
				return;
			}

			if (enemies[i].y + enemies[i].height >= 0) {
				for (int j = 0; j < ball.size(); j++) {
					if (enemies[i].isCollide(ball[j])) {
						enemies[i].kill();
						ball[j].kill();
					}
				}
			}
		}
	}
};