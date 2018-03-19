#ifndef SPRITE_H
#define SPRITE_H


#include <GL\glew.h>
#include <glm\glm.hpp>

#include <string>
#include <memory>

#include "Texture2D.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void load(const std::string& texturePath);
	void draw();

private:
	std::string mTexturePath;
	int mWidth;
	int mHeight;

	std::shared_ptr<Texture2D> mTexture;

	GLuint mVBO;
	GLuint mIBO;
	GLuint mVAO;

	glm::vec3 mPosition;

	static GLushort mIndices[6];
};


#endif // SPRITE_H