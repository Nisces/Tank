#pragma once
#include"GameObject.h"

enum Type
{
	GRASS, BRICK, BASE, STONE, WATER, TREE, TANKBASE, BOMBT, EXTRA, EXT, EARTH
};

class Block : public GameObject
{
public:
	Block(Type type, glm::vec2 pos, glm::vec2 size);
	bool breakable;
	bool tankable;
	bool bulletable;
	int blood;
	Type type;
	void setTexture(Texture texture);
	bool isDestroy();
	bool draw(SpriteRenderer &renderer);
private:

};
