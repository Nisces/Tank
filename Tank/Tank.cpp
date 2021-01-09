#include "Tank.h"
#include "ResourceManager.h"
#include <iostream>

Tank::Tank(Position pos, Size size, float speed, int blood) : GameObject(pos, size), speed(speed), angle(0), dir(Direction::UP), blood(blood), attacked(0)
{
	this->textures.push_back(ResourceManager::getTexture("Hull_02_A"));
	this->textures.push_back(ResourceManager::getTexture("Hull_02_B"));
	this->textures.push_back(ResourceManager::getTexture("Gun_01"));
	this->rotateCenter = glm::vec2(0.5 * size.x, 0.62 * size.y);
	this->velocity = glm::vec2(0, 0);
}


bool Tank::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(this->textures[frame], pos, size, glm::radians(float(angle)), Point(-1, -1), attacked);
	renderer.drawSprite(this->textures[2], pos, size, glm::radians(float(angle)), rotation - glm::radians(static_cast<float>(angle)), rotateCenter);
	return true;
}

void Tank::move(float dt)
{
	static int rotations[] = { 0, 180, 270, 90, 315, 45, 225, 135 };
	int dr = 15;
	int direction = static_cast<int>(this->dir);
	if (rotations[direction] != angle)
	{
		int diff = rotations[direction] - angle;
		if (diff < 0)
			diff += 360;
		if (diff > 180)
		{
			dr = -dr;
		}
		else if (diff == 180)
		{
			dr = (rotations[direction] - angle) / abs(rotations[direction] - angle) * dr;
		}
		angle += dr;
		angle = (angle + 360) % 360;
	}
	if (!this->stop)
	{
		this->pos += this->velocity * dt;
	}
}

void Tank::turnTo(glm::vec2 pos)
{
	glm::vec2 center = this->pos + this->rotateCenter;
	float a = pos.x - center.x;
	float b = pos.y - center.y;
	float c = sqrt(a * a + b * b);
	float angle = glm::asin(a / c);
	if (b > 0)
	{
		angle = glm::pi<float>() - angle;
	}
	this->rotation = angle;
}

void Tank::changeDir(Direction dir)
{
	static float rotations[] = { 0, 180, 270, 90, 315, 45, 225, 135 };
	float rad = glm::radians(rotations[static_cast<int>(dir)]);
	this->velocity = glm::vec2(speed * sin(rad), -speed * cos(rad));
	this->dir = dir;
	this->stop = false;
}
