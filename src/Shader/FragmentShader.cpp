#include "FragmentShader.h"
#include "ShaderException.h"
#include <cstring>

namespace librender
{

	FragmentShader::FragmentShader(const char *data)
	{
		this->id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->id, 1, &data , NULL);
		glCompileShader(this->id);
		GLint result = GL_FALSE;
		int infoLogLength;
		glGetShaderiv(this->id, GL_COMPILE_STATUS, &result);
		glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (!result)
		{
			char *error = new char[infoLogLength + 1];
			std::memset(error, 0, infoLogLength + 1);
			glGetShaderInfoLog(this->id, infoLogLength, NULL, error);
			glDeleteShader(this->id);
			std::string err(error);
			delete[] (error);
			throw ShaderException(err);
		}
	}

	FragmentShader::~FragmentShader()
	{
		glDeleteShader(this->id);
	}

}
