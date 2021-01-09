#pragma once
#include "GameObject.h"

class BulletErase : public GameObject
{
public:
	BulletErase(Position pos, Size size ,float rotation);     //±¨’®Œª÷√  
	bool draw(SpriteRenderer& renderer);
	int count;
};
