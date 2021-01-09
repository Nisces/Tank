#include "Bonus.h"
#include"ResourceManager.h"

Bonus::Bonus(BonusType type, Position pos, Size size)   //ʵ����
{
	this->exitTime = 200;
	this->obtained = false;   //��δ��̹�˻��
	this->type = type;
	this->pos = pos;
	this->size = size;

	//��ͼ����
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
