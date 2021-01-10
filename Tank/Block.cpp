#include"Block.h"
#include"ResourceManager.h"
#include <cmath>

Block::Block(Type type, glm::vec2 pos, glm::vec2 size)
{
	Texture texture;
	switch (type)
	{
	case GRASS:
		texture = ResourceManager::getTexture("GT1");
		this->type = GRASS;
		this->breakable = false;
		this->tankable = true;
		bulletable = true;
		break;
	case BRICK:
		texture = ResourceManager::getTexture("BL1");
		this->type = BRICK;
		this->breakable = true;
		this->tankable = false;
		bulletable = false;
		break;
	case BASE:
		texture = ResourceManager::getTexture("BASE");
		this->type = BASE;
		this->breakable = true;
		this->tankable = false;
		bulletable = false;
		break;
	case STONE: texture = ResourceManager::getTexture("STONE");
		this->type = STONE;
		this->breakable = false;
		this->tankable = false;
		bulletable = false;
		break;
	case WATER:
		texture = ResourceManager::getTexture("WATER");
		this->type = WATER;
		this->breakable = false;
		this->tankable = false;
		bulletable = true;
		break;
	case TREE:
		texture = ResourceManager::getTexture("TREE");
		this->type = TREE;
		this->breakable = false;
		this->tankable = true;
		bulletable = true;
		break;
	case TANKBASE:
		texture = ResourceManager::getTexture("TANKBASE");
		this->type = TANKBASE;
		this->breakable = false;
		this->tankable = false;
		bulletable = false;
		break;
	case BOMBT:
		texture = ResourceManager::getTexture("BOMBT");
		this->type = BOMBT;
		this->breakable = true;
		this->tankable = false;
		bulletable = false;
		break;
	case EXTRA:
		texture = ResourceManager::getTexture("EXTRA");
		this->type = GRASS;
		this->breakable = false;
		this->tankable = true;
		bulletable = true;
		break;
	case EXT:
		texture = ResourceManager::getTexture("EXT");
		this->type = GRASS;
		this->breakable = false;
		this->tankable = true;
		bulletable = true;
		break;
	case EARTH:
		texture = ResourceManager::getTexture("GT2");
		this->type = GRASS;
		this->breakable = false;
		this->tankable = true;
		bulletable = true;
		break;
	default: break;
	}

	//this->tankable = true;
	this->blood = 1000;
	this->textures.push_back(texture);
	this->pos = pos;
	this->size = size;
	if (type == BRICK)
	{
		this->textures.push_back(ResourceManager::getTexture("BL2"));
		this->textures.push_back(ResourceManager::getTexture("BL3"));
		this->textures.push_back(ResourceManager::getTexture("BL4"));
		this->textures.push_back(ResourceManager::getTexture("bomblock"));
	}
	if (type == BOMBT) {
		this->blood = 100;
		this->textures.push_back(ResourceManager::getTexture("BOMBT"));
		this->textures.push_back(ResourceManager::getTexture("BOMBT"));
		this->textures.push_back(ResourceManager::getTexture("BOMBT"));
		this->textures.push_back(ResourceManager::getTexture("bombt"));

	}
	if (type == BASE)
	{
		this->textures.push_back(ResourceManager::getTexture("BASE"));
		this->textures.push_back(ResourceManager::getTexture("BASE"));
		this->textures.push_back(ResourceManager::getTexture("BASE"));
		this->textures.push_back(ResourceManager::getTexture("bomblock"));
	}
}

void Block::setTexture(Texture texture)
{
	this->textures[0] = texture;
}

bool Block::isDestroy()
{
	if (this->blood > 0) {
		return false;
	}
	else {
		return true;
	}
}

bool Block::draw(SpriteRenderer& renderer)
{
	int b = ceil(double(blood) / 250);
	b = b < 0 ? 0 : b;
	int index = 4 - b;
	renderer.drawSprite(textures[index], pos, size, rotation);
	return false;
}
