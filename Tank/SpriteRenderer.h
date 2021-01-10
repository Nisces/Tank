#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();
	void drawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, int attacked = 0);
	void drawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, GLfloat faceto, glm::vec2 rotateCenter);

private:
	Shader shader;
	unsigned int VAO;
	void initRenderer();
};

