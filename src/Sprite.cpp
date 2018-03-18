#include "Sprite.h"

#include <iostream>

Sprite::Sprite() :
	mIsLoaded(false),
	mVBO(0),
	mIBO(0),
	mVAO(0)
{
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mIBO);
	glDeleteVertexArrays(1, &mVAO);

	mVBO = 0;
	mIBO = 0;
	mVAO = 0;
}

void Sprite::load(const std::string& texturePath)
{
	mTexturePath = texturePath;

	// pass width and height as out parameters;
	mIsLoaded = mTexture.loadTexture(mTexturePath, &mWidth, &mHeight);
	if (!mIsLoaded)
	{
		std::cerr << "texture '" << mTexturePath << "' not loaded! sprite will not be initialized!" << std::endl;
		return;
	}

	GLfloat vertices[] = {
		// position	 // texture coordinates
		-1.0f, 1.0f, 0.0f, 1.0f,	// top left
		 1.0f, 1.0f, 1.0f, 1.0f,	// top right
		 1.0f,-1.0f, 1.0f, 0.0f,	// bottom right
		-1.0f,-1.0f, 0.0f, 0.0f		// bottom left
	};

	GLushort indices[] = {
		0, 1, 2,	// first triangle
		2, 3, 0		// secont triangle
	};

	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);


	// texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::draw()
{
	/*if (!mIsLoaded)
	{
		return;
	}
	*/
	glBindVertexArray(mVAO);
	mTexture.bind(0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	mTexture.unbind(0);
	glBindVertexArray(0);
}

int Sprite::getWidth() const
{
	return mWidth;
}

int Sprite::getHeight() const
{
	return mHeight;
}
