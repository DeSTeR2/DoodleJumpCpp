#pragma once

#include <Vector>
#include "BallFire.h"
#include "Player.h"

#define ff first
#define ss second

class BallController {
private:
	vector <BallFire> balls;
	Player& player;
	float speed = 0;
	int windowWidth, windowHeight;

public:
	BallController(Player& player, float speed, int windowWidth, int windowHeight) : player(player), speed(speed), windowWidth(windowWidth), windowHeight(windowHeight){

	}

	void createBall(pair<int,int> mousePosition) {


		pair<double, double> pos = { player.posX + player.width / 2, player.posY + player.height / 2 };
		BallFire ball({ mousePosition.ff - pos.ff, mousePosition.ss - pos.ss }, speed, pos);
		balls.push_back(ball);
	}

	void draw() {
		vector<BallFire> newBall;
		for (int i = 0; i < balls.size(); i++) {
			balls[i].move();
			balls[i].draw();
			if (balls[i].outOfWindow(windowWidth, windowHeight)) {
				balls[i].destroy();
			}
			else newBall.push_back(balls[i]);
		}
		balls = newBall;
	}
};