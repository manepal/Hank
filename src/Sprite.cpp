#include "Sprite.h"

#include <iostream>

#include "Vertex.h"


GLushort Sprite::mIndices[6] = {
	0, 1, 2,
	2, 3, 0
};

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

	Vertex vertices[4];
	// top left
	vertices[0].setPosition(-1.0f, 1.0f);
	vertices[0].setUV(0.0f, 1.0f);
	vertices[0].setColor(255, 255, 255, 255);
	
	// top right
	vertices[1].setPosition(1.0f, 1.0f);
	vertices[1].setUV(1.0f, 1.0f);
	vertices[1].setColor(255, 255, 255, 255);
	
	// bottom right
	vertices[2].setPosition(1.0f, -1.0f);
	vertices[2].setUV(1.0f, 0.0f);
	vertices[2].setColor(255, 255, 255, 255);
	
	// bottom left
	vertices[3].setPosition(-1.0f, -1.0f);
	vertices[3].setUV(0.0f, 0.0f);
	vertices[3].setColor(255, 255, 255, 255);

	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(0);

	// texcoords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Position)));
	glEnableVertexAttribArray(1);

	// color attribute
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)(sizeof(Position) + sizeof(UV)));
	glEnableVertexAttribArray(2);

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
