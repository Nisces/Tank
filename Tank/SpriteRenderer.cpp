#include "SpriteRenderer.h"
#include <iostream>


SpriteRenderer::SpriteRenderer(const Shader& shader)
{
	this->shader = shader;
	this->initRenderer();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);
}


void SpriteRenderer::drawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, int attacked)
{
	// Prepare transformations
	this->shader.use();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	//确定旋转中心
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);
	this->shader.SetInteger("attacked", attacked);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::drawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, GLfloat faceto, glm::vec2 rotateCenter)
{
	// Prepare transformations
	this->shader.use();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	//确定旋转中心
	model = glm::translate(model, glm::vec3(glm::vec2(0.5f * size.x, 0.5f * size.y), 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-glm::vec2(0.5f * size.x, 0.5f * size.y), 0.0f)); // Move origin back

	model = glm::translate(model, glm::vec3(rotateCenter, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, faceto, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-rotateCenter, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);
	this->shader.SetInteger("attacked", 0);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderer()
{
	unsigned int VBO;
	unsigned int EBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}