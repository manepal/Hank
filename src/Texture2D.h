#ifndef	TEXTURE_2D_H
#define TEXTURE_2D_H

#include <GL\glew.h>
#include <string>


class Texture2D
{
public:
	Texture2D();
	virtual ~Texture2D();

	bool loadTexture(const std::string& filename, bool generateMipmaps = true);
	void bind(GLuint texUnit = 0);
	void unbind(GLuint texUnit = 0);

	// getters
	int getWidth();
	int getHeight();

private:
	GLuint mTexture;
	int mWidth;
	int mHeight;
};


#endif // TEXTURE_2D_H