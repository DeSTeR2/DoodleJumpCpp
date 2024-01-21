#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <windows.h>
#include <sstream>
using namespace std;

#include "Framework.h"
#include "GamePlatforms.h"
#include "Player.h"
#include "BallController.h"
#include "ScoreManager.h"
#include "CoinsManager.h"
#include "EnemyController.h"

#pragma comment(lib, "FrameworkRelease_x64.lib")


bool stopProgram = false;

string args = "game -window";

int windowWidth = 1000;
int windowHeight = 800;

int platformNumber = 50;
int spawnPlatform = -250;
int destroyPlatform = windowHeight;
int coinNumber = 10;

int enemyNumber = 4, spawnEnemyY = -200;

double ballSpeed = 2.1;

bool fullScreen = false;


class Game : public Framework {
	Player* player;
	GamePlatforms* gamePlatforms;
	BallController* ballController;
	ScoreManager* scoreManager;
	CoinsManager* coinsManager;
	EnemyController* enemyController;

	Sprite* backGround;

	pair<int, int> mousePos = { 0,0 };
	int width, height, dirX=0,dirY=0;


	void draw() {
		drawSprite(backGround, 0, 0);
		gamePlatforms->draw();
		player->draw();
		ballController->draw();
		coinsManager->draw();
		enemyController->draw(*ballController, *player, *gamePlatforms);

		int score = gamePlatforms->getScore();
		int passedPlatforms = gamePlatforms->getPassedPlatforms();
		int playerHealth = player->health;
		int playerCoins = player->getCoin();
		scoreManager->draw(score, passedPlatforms, playerHealth, playerCoins);
	}

	void move() {
		gamePlatforms->move(*player);
		player->move();
		coinsManager->move(*gamePlatforms);
		enemyController->move(*gamePlatforms);
	}
	
	void createNewGame(bool create) {
		if (!create) return;
		delete player;
		delete gamePlatforms;
		delete ballController;
		delete scoreManager;
		delete coinsManager;
		delete enemyController;

		player = new Player(windowWidth, windowHeight);
		gamePlatforms = new GamePlatforms(int((windowWidth+ windowHeight)*0.2), spawnPlatform, destroyPlatform, windowWidth, windowHeight, *player);
		ballController = new BallController(*player, ballSpeed, windowWidth, windowHeight);
		scoreManager = new ScoreManager(20, 20, windowWidth, windowHeight);
		coinsManager = new CoinsManager(*player, coinNumber, windowWidth, windowHeight);
		enemyController = new EnemyController(enemyNumber, spawnEnemyY, windowWidth, windowHeight, *gamePlatforms);

		backGround = createSprite(".\\data\\bck@2x.png");
		int wid, hei;
		getSpriteSize(backGround, wid, hei);
		setSpriteSize(backGround, width, hei);
	}

	void checkNull() {
		if (player == nullptr) createNewGame(1);
		if (gamePlatforms == nullptr) createNewGame(1);
		if (ballController == nullptr) createNewGame(1);
		if (scoreManager == nullptr) createNewGame(1);
		if (coinsManager == nullptr) createNewGame(1);
		if (enemyController == nullptr) createNewGame(1);

	}

public:


	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = windowWidth;
		height = windowHeight;
		this->width = width;
		this->height = height;
		fullscreen = false;
	}

	virtual bool Init() {  
		PreInit(windowWidth, windowHeight, fullScreen);
		createNewGame(true);
		return true;
	}

	virtual void Close() {
		delete player;
		delete gamePlatforms;
		delete ballController;
		delete scoreManager;
		delete coinsManager;
		delete enemyController;
	}


	virtual bool Tick() {
		checkNull();
		createNewGame(player->isDead());
		
		draw();
		move();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		mousePos = {x,y};
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		switch (button)
		{
		case FRMouseButton::LEFT:
			if (isReleased == false) ballController->createBall(mousePos);
			break;
		case FRMouseButton::MIDDLE:
			break;
		case FRMouseButton::RIGHT:
			player->setSpringBoot();
			break;
		case FRMouseButton::COUNT:
			break;
		default:
			break;
		}
	}
	
	virtual void onKeyPressed(FRKey k) {
		
		switch (k) {
		case FRKey::RIGHT:
			player -> dirX = 1;
			break;
		case FRKey::LEFT:
			player->dirX = -1;
			break;
		case FRKey::UP:
			player->dirY = -1;
			break;
		case FRKey::DOWN:
			player->dirY = 1;
			break;
		}

		
	}

	virtual void onKeyReleased(FRKey k) {
		switch (k) {
		case FRKey::RIGHT:
			player->dirX = 0;
			break;
		case FRKey::LEFT:
			player->dirX = 0;
			break;
		case FRKey::UP:
			player->dirY = 0;
			break;
		case FRKey::DOWN:
			player->dirY = 0;
			break;
		}
	}

	virtual const char* GetTitle() override
	{
		return "ZaharVlasenko Game (defens213@gmail.com)";
	}
};

int main(int argc, char* argv[]) { 
	srand(time(0));
	
	if (argc >= 4) {
		string first(argv[1]);
		string second(argv[2]);
		
		if (first + ' ' + second == args) {

			string arg(argv[3]);
			string width, height;
			bool sec = false;
			for (int i = 0; i < arg.size(); i++) {
				if (arg[i] == 'x') sec = true;
				if (!sec) width += arg[i];
				else if (arg[i] != 'x') height += arg[i];
			}

			windowWidth = atoi(width.c_str());
			windowHeight = atoi(height.c_str());

			cout << "Window size set to: " << windowWidth << "x" << windowHeight << '\n';
		}
	}

	
	Game* game = new Game;

	return run(game);
}
