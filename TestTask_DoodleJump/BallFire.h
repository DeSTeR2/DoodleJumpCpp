#pragma once

#include "Framework.h"
#include "Player.h"
#include <vector>

#define ff first
#define ss second

class BallFire {
private:
	Sprite* sprite;
	pair<double, double> vectorToMove;
	int speed;
	double x=-1e9, y=-1e9;


	double VectorMadnitude() {
		return sqrt(vectorToMove.ff * vectorToMove.ff + vectorToMove.ss * vectorToMove.ss);
	}

	pair<double, double> Normalize() {
		double madnitude = VectorMadnitude();
		return { vectorToMove.ff/madnitude, vectorToMove.ss/madnitude };
	}

public:

	BallFire() {
		sprite = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\ball.png");
	}
	BallFire(pair<double, double> vector, int speed, pair<double, double> position) {
		vectorToMove = vector;
		//cout << vectorToMove.ff << " " << vectorToMove.ss << "|";
		vectorToMove = Normalize();
		//cout << vectorToMove.ff << " " << vectorToMove.ss << endl;
		this->speed = speed;
		x = position.ff;
		y = position.ss;
		sprite = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\ball.png");
	}

	void move() {
		x += vectorToMove.ff * speed;
		y += vectorToMove.ss * speed;
	}

	void draw() {
		if(x!=-1e9 || y!=-1e9) drawSprite(sprite, x, y);
	}

	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool outOfWindow(int width, int height) {
		return x > width || x < 0 || y<0 || y>height;
	}

	void destroy() {
		destroySprite(sprite);
	}
};