#include "BulletErase.h"
#include "ResourceManager.h"
#include <iostream>

BulletErase::BulletErase(Position pos, Size size, int damage) : GameObject(pos, size), damage(damage)
{
	this->count = 0;
	this->textures.push_back(ResourceManager::getTexture("BE1"));
	this->textures.push_back(ResourceManager::getTexture("BE2"));
}

bool BulletErase::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(textures[count], pos, size, rotation);
	return false;
}


