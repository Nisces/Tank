#pragma once
#include "Tank.h"
#include "Game.h"
#include <vector>

using namespace std;

class AIController
{
public:
	static void AI(Game &game, float dt);
	static void generateEnemy(Game& game, float dt);
};

