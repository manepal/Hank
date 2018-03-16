#ifndef SPRITE_H
#define SPRITE_H


#include <GL\glew.h>
#include <glm\glm.hpp>

#include <string>

#include "Texture2D.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void load(const std::string& texturePath);
	void draw();

	int getWidth() const;
	int getHeight() const;

private:
	std::string mTexturePath;
	int mWidth;
	int mHeight;
	bool mIsLoaded;

	Texture2D mTexture;

	GLuint mVBO;
	GLuint mIBO;
	GLuint mVAO;

	glm::vec3 mPosition;
};


#endif // SPRITE_H