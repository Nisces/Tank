#pragma once
#include <map>
#include <string>
#include "Shader.h"
#include "Texture.h"

using namespace std;

class ResourceManager
{
public:
	static Shader loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, string name);
	static Shader getShader(string name);
	static Texture loadTexture(const char* file, string name);
	static Texture getTexture(string name);
private:
	ResourceManager() {}  //��̬�࣬����Ҫ�������Ķ���
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture loadTextureFromFile(const char* file);
	static map<string, Shader> shaders;
	static map<string, Texture> textures;
};

