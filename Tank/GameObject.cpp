#include "GameObject.h"

GameObject::GameObject() :pos(Position(0, 0)), size(Size(10, 10)), velocity(Velocity(10, 10)), rotation(0), rotateCenter(Point(-1, -1)), isEnemy(false)
{
}

GameObject::GameObject(Position pos, Size size, Velocity velocity, float rotation, Point rotateCenter)
	: pos(pos), size(size), velocity(velocity), rotation(rotation), rotateCenter(rotateCenter), isEnemy(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::addTexture(Texture texture)
{
	this->textures.push_back(texture);
}
    
bool GameObject::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(textures[0], pos, size, rotation);
	return false;
}
