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
	void spawnBonus(GameObject& obj);
	void updateBonus(float dt);
	void updateView();
	int render();
	void drawUI();
	void processInput(float dt);
	void resetPlayer();
	void resetLevel();

public:
	bool keys[1024] = { false };
	bool mouseKeys[5] = { false };
	bool mouseKeysProcessed[5] = { false };
	Point mousePos;
	bool keysProcessed[1024] = { false };
	unsigned int width, height;

public:
	Tank *player;
	vector<Bullet> bullets;
	vector<Explosion> explosions;
	vector<BulletErase> bulleterase;
	vector<Tank> tanks;
	vector<GameLevel> levels;
	vector<Bonus> bonusItems;
	unsigned int level;
	unsigned int lvlHeight = 1000, lvlWidth = 1000;
	Size viewSize;
	Position camPostion;
	int lives = 3;
private:
	const float FPS = 30;
};

