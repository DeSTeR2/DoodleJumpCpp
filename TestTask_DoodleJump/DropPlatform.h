#pragma once

#include "Platform.h"

class DropPlatform : Platform {
	DropPlatform() {
		platform = createSprite("D:\\Codes\\C++\\TestTask_doodlejump\\TestTask_DoodleJump\\TestTask_DoodleJump\\sprites\\fall-platform1.png");
	}
};