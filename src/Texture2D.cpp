#include "Texture2D.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image\stb_image.h>

Texture2D::Texture2D() :
	mTexture(0)
{
}

Texture2D::~Texture2D()
{
	mTexture = 0;
}

bool Texture2D::loadTexture(const std::string & filename, bool generateMipmaps)
{
	int components;

	unsigned char* imageData = stbi_load(filename.c_str(), &mWidth, &mHeight, &components, STBI_rgb_alpha);
	if (imageData == nullptr)
	{
		std::cerr << "error loading texture /'" << filename << "/'!" << std::endl;
		return false;
	}

	// Invert image
	int widthInBytes = mWidth * 4;
	unsigned char *top = nullptr;
	unsigned char *bottom = nullptr;
	unsigned char temp = 0;
	int halfHeight = mHeight / 2;
	for (int row = 0; row < halfHeight; row++)
	{
		top = imageData + row * widthInBytes;
		bottom = imageData + (mHeight - row - 1) * widthInBytes;
		for (int col = 0; col < widthInBytes; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	if (generateMipmaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Texture2D::bind(GLuint texUnit)
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

void Texture2D::unbind(GLuint texUnit)
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture2D::getWidth()
{
	return mWidth;
}

int Texture2D::getHeight()
{
	return mHeight;
}
