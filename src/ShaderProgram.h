#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H


#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <map>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();
	void unUse();

	void setUniformSampler(const GLchar* name, GLint& slot);
	void setUniform(const GLchar* name, GLfloat& f);
	void setUniform(const GLchar* name, glm::vec2& v);
	void setUniform(const GLchar* name, glm::vec3& v);
	void setUniform(const GLchar* name, glm::vec4& v);
	void setUniform(const GLchar* name, glm::mat4& m);

	GLuint getProgram() const;

private:
	GLuint mProgramHandle;
	std::map<std::string, GLint> mUniformLocations;

private:
	std::string fileToString(const std::string& filename);
	void checkCompilationErrors(GLuint shader, const std::string& filename);
	void checkLinkErrors();

	GLint getUniformLocation(const GLchar* name);
};


#endif // SHADER_PROGRAM_H