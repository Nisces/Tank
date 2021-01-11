#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "Texture.h"
#include "SpriteRenderer.h"

using namespace std;

typedef glm::vec2 Point;
typedef glm::vec2 Position;
typedef glm::vec2 Size;
typedef glm::vec2 Velocity;
typedef glm::vec3 Color;

class GameObject
{
public:
	GameObject();
	GameObject(Position pos, Size size = Size(10, 10), Velocity velocity = Velocity(0, 0), float rotation = 0.0f);
	~GameObject();
	void addTexture(Texture texture);
	virtual bool draw(SpriteRenderer &renderer);
	bool operator==(const GameObject& rhs) const;
public:
	static int count;
	int id;
	glm::vec2 pos, size, velocity;  //位置先x后y，大小先宽后高
	float rotation;
	vector<Texture> textures;
	bool isEnemy = false;
};

