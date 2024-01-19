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
			//if (!enemies[i]) continue;
			enemies[i].setPosition(enemies[i].x, enemies[i].y + amount);
		}
	}

	void moveToTarget() {
		if (targetY == 0) return;
		targetY--;
		this->moveDown(3.0 * speed);
	}

	void createNew(int i, GamePlatforms& gamePlatforms) {
		//if (!enemies[i]) return;
		//delete enemies[i];
		//enemies.erase(enemies.begin() + i, enemies.begin() + i + 1);

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
			//if (!enemies[i]) continue;
			if (enemies[i].y > windowHeight) createNew(i, gamePlatforms);
		}
	}

	void draw(BallController& balls, Player& player, GamePlatforms& gamePlatforms) {
		for (int i = 0; i < EnemyNumber; i++) {
			//if (enemies[i]) 
				enemies[i].draw();
		}
		vector<BallFire>& ball = balls.getBalls();
		for (int i = 0; i < EnemyNumber; i++) {
			//if (!enemies[i]) continue;
			if (enemies[i].isKilled()) continue;

			if (enemies[i].isCollide(player)) {


				//cout << player.lowestPlatform.first << " " << player.lowestPlatform.second << endl;
				gamePlatforms.setLowestPlatformOnPlayer(player);
				//cout << player.lowestPlatform.first << " " << player.lowestPlatform.second << endl;

				player.reduseHealth();
			}

				if (enemies[i].y + enemies[i].height >= 0) {
					for (int j = 0; j < ball.size(); j++) {
						//cout << "Enemy pos: " << enemies[i]->x << " " << enemies[i]->y << endl << "Ball pos: "<;
						if (enemies[i].isCollide(ball[j])) {
							//cout << "KILLL\n";
							enemies[i].kill();
							ball[j].kill();
						}
					}
				}
		}
	}
};