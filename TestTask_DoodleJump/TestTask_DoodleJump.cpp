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

#pragma comment(lib, "FrameworkRelease_x64.lib")


int windowWidth = 800;
int windowHeight = 600;

int platformNumber = 40;
int spawnPlatform = -300;
int destroyPlatform = windowHeight + 100;

double ballSpeed = 2.1;

bool fullScreen = false;

class Game : public Framework {
	Player* player;
	GamePlatforms* gamePlatforms;
	BallController* ballController;


	pair<int, int> mousePos = { 0,0 };
	int width, height, dirX=0,dirY=0;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		//player.setPosition(100, 100);
		this->width = width;
		this->height = height;
		fullscreen = false;
	}

	virtual bool Init() {
		gamePlatforms = new GamePlatforms(platformNumber, spawnPlatform, destroyPlatform, width, height);
		player = new Player(10,10);
		ballController = new BallController(*player, ballSpeed, windowWidth, windowHeight);

		return true;
	}

	virtual void Close() {

	}


	virtual bool Tick() {
		gamePlatforms->draw();
		player->draw();
		ballController->draw();

		gamePlatforms->move(*player);
		//gamePlatforms->moveDown(1);

		//player.setPosition(100, 100);
		player->move();
		
		//drawTestBackground();
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
