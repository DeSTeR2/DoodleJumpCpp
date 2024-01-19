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
	double speed;
	bool killed = false;


	double VectorMadnitude() {
		return sqrt(vectorToMove.ff * vectorToMove.ff + vectorToMove.ss * vectorToMove.ss);
	}

	pair<double, double> Normalize() {
		double madnitude = VectorMadnitude();
		return { vectorToMove.ff/madnitude, vectorToMove.ss/madnitude };
	}

public:
	double x=-1e9, y=-1e9;
	int width, height;

	BallFire() {
		sprite = createSprite(".\\sprites\\ball.png");
		getSpriteSize(sprite, width, height);
	}
	BallFire(pair<double, double> vector, int speed, pair<double, double> position) {
		vectorToMove = vector;
		//cout << vectorToMove.ff << " " << vectorToMove.ss << "|";
		vectorToMove = Normalize();
		//cout << vectorToMove.ff << " " << vectorToMove.ss << endl;
		this->speed = speed;
		x = position.ff;
		y = position.ss;
		sprite = createSprite(".\\sprites\\ball.png");
	}

	//bool checkCollide(Enemy enemy) {
	//	return enemy.isCollide(*this);
	//}

	void move() {

		if (killed) x = -100;

		x += vectorToMove.ff * speed;
		y += vectorToMove.ss * speed;
	}

	void draw() {
		if (killed) return;
		if(x!=-1e9 || y!=-1e9) drawSprite(sprite, int(x), int(y));
	}

	void setPosition(double x, double y) {
		this->x = x;
		this->y = y;
	}

	bool outOfWindow(int width, int height) {
		return x > width || x < 0 || y<0 || y>height;
	}

	void kill() {
		killed = true;
	}

	void destroy() {
		destroySprite(sprite);
	}
};