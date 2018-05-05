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

	void ProgramLocation::setVec2i(GLint val1, GLint val2)
	{
		glUniform2i(this->location, val1, val2);
	}

	void ProgramLocation::setVec3i(GLint val1, GLint val2, GLint val3)
	{
		glUniform3i(this->location, val1, val2, val3);
	}

	void ProgramLocation::setVec4i(GLint val1, GLint val2, GLint val3, GLint val4)
	{
		glUniform4i(this->location, val1, val2, val3, val4);
	}

	void ProgramLocation::setVec1f(GLfloat val)
	{
		glUniform1f(this->location, val);
	}

	void ProgramLocation::setVec2f(GLfloat val1, GLfloat val2)
	{
		glUniform2f(this->location, val1, val2);
	}

	void ProgramLocation::setVec2f(Vec2 &vec)
	{
		glUniform2f(this->location, vec.x, vec.y);
	}

	void ProgramLocation::setVec3f(GLfloat val1, GLfloat val2, GLfloat val3)
	{
		glUniform3f(this->location, val1, val2, val3);
	}

	void ProgramLocation::setVec3f(Vec3 &vec)
	{
		glUniform3f(this->location, vec.x, vec.y, vec.z);
	}

	void ProgramLocation::setVec4f(GLfloat val1, GLfloat val2, GLfloat val3, GLfloat val4)
	{
		glUniform4f(this->location, val1, val2, val3, val4);
	}

	void ProgramLocation::setVec4f(Vec4 &vec)
	{
		glUniform4f(this->location, vec.x, vec.y, vec.z, vec.w);
	}

	void ProgramLocation::setMat3f(Mat3 &mat)
	{
		glUniformMatrix3fv(this->location, 1, GL_FALSE, &mat[0][0]);
	}

	void ProgramLocation::setMat4f(Mat4 &mat)
	{
		glUniformMatrix4fv(this->location, 1, GL_FALSE, &mat[0][0]);
	}

	void ProgramLocation::setVertexBuffer(VertexBuffer &buffer)
	{
		buffer.bind(GL_ARRAY_BUFFER);
		glVertexAttribPointer(this->location, buffer.getStride(), buffer.getType(), GL_FALSE, 0, nullptr);
	}

	void ProgramLocation::setVertexAttribArray(bool asArray)
	{
		if (asArray)
			glEnableVertexAttribArray(this->location);
		else
			glDisableVertexAttribArray(this->location);
	}

}
