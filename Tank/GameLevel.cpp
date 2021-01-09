#include "GameLevel.h"
#include <sstream>
#include <fstream>
#include "ResourceManager.h"
#include <random>

void GameLevel::load(const GLchar* file, GLuint levelWidth, GLuint levelHeight)
{
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode)  //读取文件内容，砖块信息
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(levelWidth, levelHeight);
	}
}

void GameLevel::draw(SpriteRenderer& renderer)
{
	for (Block b : this->background)
	{
		b.draw(renderer);
	}
	for (Block b : this->blocks)
	{
		b.draw(renderer);
	}
	for (Block b : this->tankBase)
	{
		b.draw(renderer);
	}
}

void GameLevel::drawTree(SpriteRenderer& renderer)
{
	for (Block b : this->tree) {
		b.draw(renderer);
	}
}

void GameLevel::init(GLuint levelWidth, GLuint levelHeight)
{
	height = tileData.size();
	width = tileData[0].size();
	unit_width = levelWidth / static_cast<GLfloat>(width);
	unit_height = levelHeight / height;
	for (GLuint i = 0; i < height; ++i)
	{
		for (GLuint j = 0; j < width; ++j)
		{
			int a = rand() % 2;
			if (a == 0) 
			{
				this->background.push_back(Block(GRASS, glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
			}
			if (a == 1)
			{
				this->background.push_back(Block(EARTH, glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
			}
		}
	}
	for (GLuint i = 0; i < height; ++i)
	{
		for (GLuint j = 0; j < width; ++j)
		{
			if (tileData[i][j])
			{
				if (tileData[i][j] == 5) {
					this->tree.push_back(Block(Type(tileData[i][j]), glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
				}
				else if (tileData[i][j] == 8) {
					this->tree.push_back(Block(Type(5), glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width * 2, unit_height * 2)));
				}
				else if (tileData[i][j] == 6) {
					this->tankBase.push_back(Block(Type(tileData[i][j]), glm::vec2(j * unit_width, i * unit_height), glm::vec2(3 * unit_width, unit_height)));
				}
				else if (tileData[i][j] == 2) {
					this->blocks.insert(blocks.begin(), Block(Type(tileData[i][j]), glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
				}
				else {
					this->blocks.push_back(Block(Type(tileData[i][j]), glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
				}
			}
			else
			{
				if (rand() % 40 == 0)
				{
					this->background.push_back(Block(Type(8), glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
				}
				if (rand() % 42 == 0)
				{
					this->background.push_back(Block(Type(9), glm::vec2(j * unit_width, i * unit_height), glm::vec2(unit_width, unit_height)));
				}
			}
		}
	}

}
