#include "FragmentShader.h"
#include <exception>
#include <iostream>
#include <cstring>

namespace librender
{

	FragmentShader::FragmentShader(const char *data, size_t len)
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
			if (this->id)
				glDeleteShader(this->id);
			std::cout << error << std::endl;
			delete[] (error);
			throw std::exception();
		}
	}

	FragmentShader::~FragmentShader()
	{
		if (this->id)
			glDeleteShader(this->id);
	}

}
