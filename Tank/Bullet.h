#pragma once
#include "GameObject.h"
#include "GameObject.h"


class Bullet : public GameObject
{
public:
	Bullet(glm::vec2 pos, float rotation, float speed = 1000, int damage = 250);
	bool biu(float dt, glm::vec2 winSize);
	int damage;
private:
	float speed;
};
