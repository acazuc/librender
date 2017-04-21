#include "Program.h"
#include <exception>
#include <iostream>
#include <cstring>

namespace librender
{

	Program::Program(FragmentShader *fragmentShader, VertexShader *vertexShader)
	: fragmentShader(fragmentShader)
	, vertexShader(vertexShader)
	, id(0)
	{
		if (!fragmentShader || !vertexShader)
			throw std::exception();
	 	this->id = glCreateProgram();
		glAttachShader(this->id, this->vertexShader->getId());
		glAttachShader(this->id, this->fragmentShader->getId());
		glLinkProgram(this->id);
		GLint result = GL_FALSE;
		int infoLogLength;
		glGetProgramiv(this->id, GL_LINK_STATUS, &result);
		glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (!result)
		{
			char *error = new char[infoLogLength + 1];
			std::memset(error, 0, infoLogLength + 1);
			glGetShaderInfoLog(this->id, infoLogLength, NULL, error);
			if (this->id)
				glDeleteProgram(this->id);
			std::cout << error << std::endl;
			delete[] (error);
			throw std::exception();
		}
	}

	Program::~Program()
	{
		if (this->id)
			glDeleteProgram(this->id);
	}

	void Program::use()
	{
		glUseProgram(this->id);
	}

}
