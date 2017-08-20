#include "Program.h"
#include "ProgramException.h"
#include <cstring>

namespace librender
{

	Program::Program()
	{
		this->id = glCreateProgram();
	}

	Program::~Program()
	{
		glDeleteProgram(this->id);
	}

	void Program::attachShader(FragmentShader *fragmentShader)
	{
		glAttachShader(this->id, fragmentShader->getId());
	}

	void Program::detachShader(FragmentShader *fragmentShader)
	{
		glDetachShader(this->id, fragmentShader->getId());
	}

	void Program::attachShader(GeometryShader *geometryShader)
	{
		glAttachShader(this->id, geometryShader->getId());
	}

	void Program::detachShader(GeometryShader *geometryShader)
	{
		glDetachShader(this->id, geometryShader->getId());
	}

	void Program::attachShader(VertexShader *vertexShader)
	{
		glAttachShader(this->id, vertexShader->getId());
	}

	void Program::detachShader(VertexShader *vertexShader)
	{
		glDetachShader(this->id, vertexShader->getId());
	}

	void Program::link()
	{
		glLinkProgram(this->id);
		GLint result = GL_FALSE;
		int infoLogLength;
		glGetProgramiv(this->id, GL_LINK_STATUS, &result);
		glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (!result)
		{
			char *error = new char[infoLogLength + 1];
			std::memset(error, 0, infoLogLength + 1);
			glGetProgramInfoLog(this->id, infoLogLength, NULL, error);
			std::string err(error);
			delete[] (error);
			throw ProgramException(err);
		}
	}

	ProgramLocation *Program::getUniformLocation(const char *name)
	{
		return (new ProgramLocation(glGetUniformLocation(this->id, name)));
	}

	ProgramLocation *Program::getAttribLocation(const char *name)
	{
		return (new ProgramLocation(glGetAttribLocation(this->id, name)));
	}

	void Program::use()
	{
		glUseProgram(this->id);
	}

}
