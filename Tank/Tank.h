#pragma once
#include "GameObject.h"

enum class Direction
{
	UP = 0, DOWN, LEFT, RIGHT,
	UL, UR, DL, DR,
};

class Tank : public GameObject
{
public:
	Tank(Position pos, Size size = Size(50, 50), float speed = 200, int blood = 1000);
	bool draw(SpriteRenderer& renderer);
	void move(float dt);
	void turnTo(glm::vec2 pos);
	void changeDir(Direction dir);
	Direction dir;
public:
	int angle;
	float speed;
	int blood;
	int attacked;
	bool armor = false;
	bool stop = false;
	int frame = 0;
};

