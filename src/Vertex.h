#ifndef VERTEX_H
#define VERTEX_H


#include <GL\glew.h>

struct Position
{
	GLfloat x;
	GLfloat y;
};

struct UV
{
	GLfloat u;
	GLfloat v;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex
{
	Position position;
	UV uv;
	Color color;

	void setPosition(GLfloat x, GLfloat y)
	{
		position.x = x;
		position.y = y;
	}

	void setUV(GLfloat u, GLfloat v)
	{
		uv.u = u;
		uv.v = v;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
};


#endif // VERTEX_H