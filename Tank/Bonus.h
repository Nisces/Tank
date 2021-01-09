#pragma once
#ifndef	 _Tank_
#define  _Tank_
#include "GameObject.h"
#include "Tank.h"

enum class BonusType
{
	FAST, BLOOD, ARMOR
};
class Bonus : public GameObject
{
public:
	Bonus(BonusType type, Position pos, Size size);

	bool obtained;
	BonusType type;
	int exitTime;
	int leftTime;
};

#endif
