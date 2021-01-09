#include "BulletErase.h"
#include "ResourceManager.h"
#include <iostream>

BulletErase::BulletErase(Position pos, Size size, float rotation) : GameObject(pos, size, Velocity(0, 0), rotation)
{
	this->count = 0;
	this->rotation = rotation;
	this->textures.push_back(ResourceManager::getTexture("BE1"));
	this->textures.push_back(ResourceManager::getTexture("BE2"));
}

bool BulletErase::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(textures[count], pos, size, rotation);
	return false;
}


