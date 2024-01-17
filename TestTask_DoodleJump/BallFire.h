#pragma once

#include "Framework.h"
#include <vector>

class BallFire {
private:
	Sprite* sprite;
	pair<int, int> vectorToMove;
	int speed;

	BallFire(pair<int, int> vector, int speed) {
		vectorToMove = vector;
		this->speed = speed;

		sprite = createSprite("");
	}
};