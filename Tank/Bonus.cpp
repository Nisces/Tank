#include "Bonus.h"
#include"ResourceManager.h"

Bonus::Bonus(string type, Position pos, Size size)   //ʵ����
{
	this->exitTime = 30.0;   
	this->outoftime = false;

	this->validTime = 30.0;    //��Чʱ��
	this->activated = false;   //��δ��̹�˻��
	this->runout = false;   

	this->type = type;
	this->pos = pos;
	this->size = size;

	this->delay = 0;
	this->obtainable = false;
	//��ͼ����
	Texture texture;
	
	if (type == "FAST")
	{
		texture = ResourceManager::getTexture("FAST");
	}
	else if (type == "BLOOD")
	{
		texture = ResourceManager::getTexture("BLOOD");
	}
	else if (type == "ARMOR")
	{
		texture = ResourceManager::getTexture("ARMOR");
	}

	this->textures.push_back(texture);
}

/*bool Bonus::draw(SpriteRenderer& renderer)
{
	if (this->obtainable)
	{
		renderer.drawSprite(textures[0], pos, size, rotation, rotateCenter);
		return false;
	}
	return true;
}*/
