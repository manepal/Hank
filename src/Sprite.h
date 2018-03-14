#ifndef SPRITE_H
#define SPRITE_H


#include <GL\glew.h>
#include <glm\glm.hpp>

#include <string>

#include "Texture2D.h"

class Sprite
{
public:
	Sprite(const std::string& texturePath);
	~Sprite();

	void load();
	void draw();

private:
	std::string mTexturePath;
	bool mIsLoaded;

	Texture2D mTexture;

	GLuint mVBO;
	GLuint mIBO;
	GLuint mVAO;

	glm::vec3 mPosition;
};


#endif // SPRITE_H