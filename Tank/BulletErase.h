#pragma once
#include "GameObject.h"

class BulletErase : public GameObject
{
public:
	BulletErase(Position pos, Size size ,float rotation);     //��ըλ��  
	bool draw(SpriteRenderer& renderer);
	int count;
};
