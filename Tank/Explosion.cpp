#include "Explosion.h"
#include "ResourceManager.h"
#include <iostream>

Explosion::Explosion(Position pos, Size size, int damage) : GameObject(pos, size), damage(damage)
{
	this->count = 0;
	this->textures.push_back(ResourceManager::getTexture("FIRE1"));
	this->textures.push_back(ResourceManager::getTexture("FIRE2"));
	this->textures.push_back(ResourceManager::getTexture("FIRE3"));
	this->textures.push_back(ResourceManager::getTexture("FIRE4"));
	this->textures.push_back(ResourceManager::getTexture("FIRE5"));
	this->textures.push_back(ResourceManager::getTexture("FIRE6"));
	this->textures.push_back(ResourceManager::getTexture("FIRE7"));
	this->textures.push_back(ResourceManager::getTexture("FIRE8"));
}

bool Explosion::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(textures[count], pos, size, rotation);
	return false;
}


