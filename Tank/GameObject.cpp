#include "GameObject.h"

int GameObject::count = 0;
GameObject::GameObject() :pos(Position(0, 0)), size(Size(10, 10)), velocity(Velocity(10, 10)), rotation(0), isEnemy(false)
{
	id = count++;
}

GameObject::GameObject(Position pos, Size size, Velocity velocity, float rotation)
	: pos(pos), size(size), velocity(velocity), rotation(rotation), isEnemy(false)
{
	id = count++;;
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

bool GameObject::operator==(const GameObject& rhs) const
{
	return this->id == rhs.id;
}
