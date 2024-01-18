#pragma once

class ScoreManager {
	
	Sprite* number[10];
	Sprite* score;
	Sprite* passedPlatforms;
	Sprite* heart;
	Sprite* coin;

	int posX, posY;
	int width, height;
	int windowWidth, windowHeight;

	void reSize(Sprite& sprite, float spriteMulti) {
		int wid, hei;
		getSpriteSize(&sprite, wid, hei);
		setSpriteSize(&sprite, wid * spriteMulti, hei * spriteMulti);
		//getSpriteSize(&sprite, width, height);
	}

	void drawNum(int numberToDraw,int poX, int poY, Sprite* sprite) {
		string num;
		if (numberToDraw == 0) num = "0";
		while (numberToDraw > 0) {
			num = char(numberToDraw % 10 + '0') + num;
			numberToDraw /= 10;
		}

		int wid, hei;
		getSpriteSize(sprite, wid, hei);
		drawSprite(sprite, poX, poY );
		wid += 10;
		for (int i = 0; i < num.size(); i++) {
			drawSprite(number[int(num[i] - '0')], wid + poX + i * width, poY + hei / 2 - height/2);
		}
	}

public:

	ScoreManager(int x,int y, int windowWidth, int windowHeight) : posX(x), posY(y), windowWidth(windowWidth), windowHeight(windowHeight){
		string path = "D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\";
		for (int i = 0; i < 10; i++) {
			string addPath = path + char(i + '0') + ".png";
			const char* spritePath = addPath.c_str();
			//cout << spritePath << endl;
			number[i] = createSprite(spritePath);
			reSize(*number[i], 0.7);
			getSpriteSize(number[i], width, height);
		}

		score = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\score.png");
		//reSize(*score);
		
		passedPlatforms = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\passedPlatforms.png");
		reSize(*passedPlatforms, 0.15);
	
		heart = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\heart.png");
		reSize(*heart, 0.05);

		coin = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\coin.png");
		reSize(*coin, 0.08);
	}

	void draw(int scoreNum, int passedPlatformsNum, int playerHealth, int playerCoin) {
		drawNum(scoreNum,posX, posY, score);

		int wid, hei;
		getSpriteSize(score, wid, hei);

		drawNum(passedPlatformsNum, posX , posY + hei + 10, passedPlatforms);
		int hei2;
		getSpriteSize(passedPlatforms, wid, hei2);

		drawNum(playerHealth, windowWidth - 100, posY, heart);
		
		drawNum(playerCoin, posX, posY + hei + hei2 + 30, coin);
	}

};