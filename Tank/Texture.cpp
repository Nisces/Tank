#include "Texture.h"
#include <iostream>

using namespace std;

Texture::Texture() :id(0), width(0), height(0), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), filter_min(GL_NEAREST), filter_max(GL_NEAREST), image_format(GL_RGB), internal_format(GL_RGB)
{
	glGenTextures(1, &id);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}