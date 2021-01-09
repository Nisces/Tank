#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion(Position pos, Size size, int damage = 0);     //±¨’®Œª÷√  
	bool draw(SpriteRenderer& renderer);
	int count;
	int damage = 0;
};
