#include "ResourceManager.h"
#include "Bullet.h"
#include <cmath>
#include <iostream>

Bullet::Bullet(glm::vec2 pos, float rotation, float speed, int damage) : GameObject(pos, glm::vec2(6, 15)), damage(damage) //pos size    传入rotation和speed，计算得出velocity
{
	this->speed = speed;
	this->rotation = rotation;
	this->velocity = glm::vec2(this->speed * sin(rotation), -this->speed * cos(rotation));
	this->textures.push_back(ResourceManager::getTexture("Shell"));
}


bool Bullet::biu(float dt, glm::vec2 winSize)
{
	if (pos.x <= 0 - size.x || pos.x >= winSize.x || pos.y <= 0 - size.y || pos.y >= winSize.y + size.y)  //子弹什么时候删除  
		return true;
	pos.x += this->velocity.x * dt;
	pos.y += this->velocity.y * dt;
	return false;
}