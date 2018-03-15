#include "ShaderProgram.h"

#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram() :
	mProgramHandle(0)
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(mProgramHandle);
}

bool ShaderProgram::loadShaders(const char * vsFilename, const char * fsFilename)
{
	std::string vsString = fileToString(vsFilename);
	std::string fsString = fileToString(fsFilename);
	const GLchar* vsSourcePtr = vsString.c_str();
	const GLchar* fsSourcePtr = fsString.c_str();;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsSourcePtr, nullptr);
	glShaderSource(fs, 1, &fsSourcePtr, nullptr);

	glCompileShader(vs);
	checkCompilationErrors(vs, vsFilename);

	glCompileShader(fs);
	checkCompilationErrors(fs, fsFilename);

	mProgramHandle = glCreateProgram();
	glAttachShader(mProgramHandle, vs);
	glAttachShader(mProgramHandle, fs);
	glLinkProgram(mProgramHandle);

	checkLinkErrors();

	glDeleteShader(vs);
	glDeleteShader(vs);

	mUniformLocations.clear();

	return true;
}

void ShaderProgram::use()
{
	if (mProgramHandle > 0)
	{
		glUseProgram(mProgramHandle);
	}
}

void ShaderProgram::unUse()
{
	glUseProgram(0);
}

void ShaderProgram::setUniformSampler(const GLchar * name, GLint& slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	GLint loc = getUniformLocation(name);
	glUniform1i(loc, slot);
}

void ShaderProgram::setUniform(const GLchar * name, GLfloat & f)
{
	GLint loc = getUniformLocation(name);
	glUniform1f(loc, f);
}

void ShaderProgram::setUniform(const GLchar * name, glm::vec2 & v)
{
	GLint loc = getUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::setUniform(const GLchar * name, glm::vec3 & v)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const GLchar * name, glm::vec4 & v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const GLchar * name, glm::mat4 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

GLint ShaderProgram::getUniformLocation(const GLchar * name)
{
	std::map<std::string, GLint>::iterator it = mUniformLocations.find(name);

	if (it == mUniformLocations.end())
	{
		mUniformLocations[name] = glGetUniformLocation(mProgramHandle, name);
	}

	return mUniformLocations[name];
}

GLuint ShaderProgram::getProgram() const
{
	return mProgramHandle;
}

std::string ShaderProgram::fileToString(const std::string & filename)
{
	std::stringstream ss;
	std::ifstream file;

	try
	{
		file.open(filename, std::ios::in);

		if (!file.fail())
		{
			ss << file.rdbuf();
		}

		file.close();
	}
	catch (std::exception ex)
	{
		std::cerr << "error reading shader '" << filename << "'!" << ex.what() << std::endl;
	}

	return ss.str();
}

void ShaderProgram::checkCompilationErrors(GLuint shader, const std::string& filename)
{
	int status = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		std::string errorLog(length, ' ');
		glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
		std::cerr << "failed to compile shader '" << filename << "':\n" << errorLog << std::endl;
	}
}

void ShaderProgram::checkLinkErrors()
{
	int status = 0;

	glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		int length = 0;
		glGetProgramiv(mProgramHandle, GL_INFO_LOG_LENGTH, &length);

		std::string errorLog(length, ' ');
		glGetProgramInfoLog(mProgramHandle, length, &length, &errorLog[0]);
		std::cerr << "failed to link shader program:\n" << errorLog << std::endl;
	}
}