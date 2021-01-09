#include "Bonus.h"
#include"ResourceManager.h"

Bonus::Bonus(BonusType type, Position pos, Size size)   //实例化
{
	this->exitTime = 200;
	this->obtained = false;   //还未被坦克获得
	this->type = type;
	this->pos = pos;
	this->size = size;

	//贴图设置
	Texture texture;
	switch (type)
	{
	case BonusType::FAST:
		texture = ResourceManager::getTexture("FAST");
		break;
	case BonusType::BLOOD:
		texture = ResourceManager::getTexture("BLOOD");
		break;
	case BonusType::ARMOR:
		texture = ResourceManager::getTexture("ARMOR");
		break;
	default:break;
	}
	this->textures.push_back(texture);
}
