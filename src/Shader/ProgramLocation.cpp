#include "ProgramLocation.h"

namespace librender
{

	ProgramLocation::ProgramLocation(GLint location)
	: location(location)
	{
		//Empty
	}

	void ProgramLocation::setVec1i(GLint val)
	{
		glUniform1i(this->location, val);
	}

	void ProgramLocation::setVec1f(GLfloat val)
	{
		glUniform1f(this->location, val);
	}

	void ProgramLocation::setVec2f(glm::vec2 &vec)
	{
		glUniform2f(this->location, vec.x, vec.y);
	}

	void ProgramLocation::setVec3f(glm::vec3 &vec)
	{
		glUniform3f(this->location, vec.x, vec.y, vec.z);
	}

	void ProgramLocation::setVec4f(glm::vec4 &vec)
	{
		glUniform4f(this->location, vec.x, vec.y, vec.z, vec.w);
	}

	void ProgramLocation::setMat3f(glm::mat3 &mat)
	{
		glUniformMatrix3fv(this->location, 1, GL_FALSE, &mat[0][0]);
	}

	void ProgramLocation::setMat4f(glm::mat4 &mat)
	{
		glUniformMatrix4fv(this->location, 1, GL_FALSE, &mat[0][0]);
	}

	void ProgramLocation::setDataBuffer(DataBuffer &buffer)
	{
		buffer.bind(GL_ARRAY_BUFFER);
		glVertexAttribPointer(this->location, buffer.getStride(), buffer.getType(), GL_FALSE, 0, (void*)0);
	}

	void ProgramLocation::setVertexAttribArray(bool asArray)
	{
		if (asArray)
			glEnableVertexAttribArray(this->location);
		else
			glDisableVertexAttribArray(this->location);
	}

}
