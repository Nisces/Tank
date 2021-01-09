#pragma once
#ifndef	 _Tank_
#define  _Tank_
#include "GameObject.h"
#include "Tank.h"
#include <string>

enum class BonusType
{
	FAST, BLOOD, ARMOR
};
class Bonus : public GameObject
{
public:
	Bonus(string type, Position pos, Size size);
	//bool draw(SpriteRenderer& renderer);

	bool outoftime;   //道具 是否 过时
	bool activated;   //道具是否被坦克获得
	bool runout;   //道具是否失效
	int delay;   //延时显示道具
	bool obtainable; //道具显示后才可以被获取

	std::string type;
	float exitTime;
	float validTime;  //生效时间
};

#endif
