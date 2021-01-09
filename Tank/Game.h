#pragma once
#include "Tank.h"
#include "GameLevel.h"
#include "Bullet.h"
#include "Explosion.h"
#include "BulletErase.h"
#include "Bonus.h"

class Game
{
public:
	Game(unsigned int height, unsigned int width);
	~Game();
	void init();
	int update(float dt);
	int updateBonus(float dt);
	int render();
	void processInput(float dt);
	bool keys[1024] = { false };
	bool mouseKeys[5] = { false };
	bool mouseKeysProcessed[5] = { false };
	Point mousePos;
	bool keysProcessed[1024] = { false };
	unsigned int width, height;
	Tank *player;
	//Bullet list
	vector<Bullet> bullets;
	vector<Explosion> explosions;
	vector<BulletErase> bulleterase;
	vector<Tank> enemyTanks;
	vector<GameLevel> levels;
	void drawUI();
	vector<Bonus> bonusItems;
	unsigned int level;
	unsigned int lvlHeight = 1000, lvlWidth = 1000;
	Size viewSize;
	Position camPostion;
private:
	const float FPS = 30;
};

