#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace std;

#include "Framework.h"
#include "GamePlatforms.h"
#include "Player.h"
#include "BallController.h"
#include "ScoreManager.h"
#include "CoinsManager.h"

#pragma comment(lib, "FrameworkRelease_x64.lib")


int windowWidth = 800;
int windowHeight = 600;

int platformNumber = 50;
int spawnPlatform = -250;
int destroyPlatform = windowHeight + 100;
int coinNumber = 10;

double ballSpeed = 2.1;

bool fullScreen = false;


class Game : public Framework {
	Player* player;
	GamePlatforms* gamePlatforms;
	BallController* ballController;
	ScoreManager* scoreManager;
	CoinsManager* coinsManager;

	Sprite* backGround;

	pair<int, int> mousePos = { 0,0 };
	int width, height, dirX=0,dirY=0;


	void draw() {
		drawSprite(backGround, 0, 0);
		gamePlatforms->draw();
		player->draw();
		ballController->draw();
		coinsManager->draw();

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
	}
	
	void createNewGame(bool create) {
		if (!create) return;
		delete gamePlatforms;
		delete player;
		delete ballController;
		delete scoreManager;

		gamePlatforms = new GamePlatforms(platformNumber, spawnPlatform, destroyPlatform, width, height);
		player = new Player(windowWidth, windowHeight);
		ballController = new BallController(*player, ballSpeed, windowWidth, windowHeight);
		scoreManager = new ScoreManager(20, 20, windowWidth, windowHeight);
		coinsManager = new CoinsManager(*player, coinNumber, windowWidth, windowHeight);

		backGround = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\data\\bck@2x.png");
		int wid, hei;
		getSpriteSize(backGround, wid, hei);
		setSpriteSize(backGround, width, hei);
	}

public:


	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		//player.setPosition(100, 100);
		this->width = width;
		this->height = height;
		windowWidth = width;
		windowHeight = height;
		fullscreen = false;
	}

	virtual bool Init() {
		createNewGame(true);
		return true;
	}

	virtual void Close() {
		delete gamePlatforms;
		delete player;
		delete ballController;
		delete scoreManager;
	}


	virtual bool Tick() {
		createNewGame(player->isDead());
		
		draw();
		move();
		
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		mousePos = {x,y};
		//cout << x << " " << y << " " << xrelative << " " << yrelative << endl;
		//cout << player -> posX + player -> width << " " << player -> posY + player->height<< endl;
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
			//gamePlatforms->test();
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

	Game game;
	game.PreInit(windowWidth, windowHeight, fullScreen);
	// Check if command-line arguments are provided
	if (argc == 4 && std::string(argv[1]) == "-window") {
		std::istringstream widthStream(argv[2]);
		std::istringstream heightStream(argv[3]);

		if (widthStream >> windowWidth && heightStream >> windowHeight) {
			std::cout << "Window size set to: " << windowWidth << "x" << windowHeight << std::endl;
			game.PreInit(windowWidth, windowHeight, fullScreen);
		}
		else {
			std::cerr << "Invalid window size arguments. Using default size (800x600).\n";
		}
	}

	return run(new Game);
}
