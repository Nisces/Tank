#pragma once
#include<iostream>
#include"GameObject.h"
#include"Block.h"
#include<vector>

class GameLevel
{
public:
	std::vector<Block> blocks;
	std::vector<Block> background;
	std::vector<Block> tree;
	std::vector<Block> tankBase;
	std::vector<std::vector<GLuint>> tileData;
	GLuint height, width;
	GLfloat unit_height, unit_width;
	unsigned int tanks;
	// 加载地图
	void load(const GLchar* file, GLuint levelWidth, GLuint levelHeight);
	void draw(SpriteRenderer &renderer);
	void drawTree(SpriteRenderer &renderer);

private:
	// 初始化地图砖块
	void init(GLuint levelWidth, GLuint levelHeight);
};
