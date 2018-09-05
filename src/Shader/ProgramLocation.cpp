#include "ProgramLocation.h"

namespace librender
{

	ProgramLocation::ProgramLocation()
	: location(0)
	{
		//Empty
	}

	ProgramLocation::ProgramLocation(GLint location)
	: location(location)
	{
		//Empty
	}

	void ProgramLocation::setVec1i(GLint val)
	{
		glUniform1i(this->location, val);
	}

	void ProgramLocation::setVec1iv(GLint *val, GLsizei count)
	{
		glUniform1iv(this->location, count, val);
	}

	void ProgramLocation::setVec2i(GLint val1, GLint val2)
	{
		glUniform2i(this->location, val1, val2);
	}

	void ProgramLocation::setVec2i(TVec2<GLint> val)
	{
		glUniform2i(this->location, val.x, val.y);
	}

	void ProgramLocation::setVec2iv(TVec2<GLint> *val, GLsizei count)
	{
		glUniform2iv(this->location, count, &val[0][0]);
	}

	void ProgramLocation::setVec3i(GLint val1, GLint val2, GLint val3)
	{
		glUniform3i(this->location, val1, val2, val3);
	}

	void ProgramLocation::setVec3i(TVec3<GLint> val)
	{
		glUniform3i(this->location, val.x, val.y, val.z);
	}

	void ProgramLocation::setVec3iv(TVec3<GLint> *val, GLsizei count)
	{
		glUniform3iv(this->location, count, &val[0][0]);
	}

	void ProgramLocation::setVec4i(GLint val1, GLint val2, GLint val3, GLint val4)
	{
		glUniform4i(this->location, val1, val2, val3, val4);
	}

	void ProgramLocation::setVec4i(TVec4<GLint> val)
	{
		glUniform4i(this->location, val.x, val.y, val.z, val.w);
	}

	void ProgramLocation::setVec4iv(TVec4<GLint> *val, GLsizei count)
	{
		glUniform4iv(this->location, count, &val[0][0]);
	}

	void ProgramLocation::setVec1f(GLfloat val)
	{
		glUniform1f(this->location, val);
	}

	void ProgramLocation::setVec1fv(GLfloat *val, GLsizei count)
	{
		glUniform1fv(this->location, count, val);
	}

	void ProgramLocation::setVec2f(GLfloat val1, GLfloat val2)
	{
		glUniform2f(this->location, val1, val2);
	}

	void ProgramLocation::setVec2f(TVec2<GLfloat> val)
	{
		glUniform2f(this->location, val.x, val.y);
	}

	void ProgramLocation::setVec2fv(TVec2<GLfloat> *val, GLsizei count)
	{
		glUniform2fv(this->location, count, &val[0][0]);
	}

	void ProgramLocation::setVec3f(GLfloat val1, GLfloat val2, GLfloat val3)
	{
		glUniform3f(this->location, val1, val2, val3);
	}

	void ProgramLocation::setVec3f(TVec3<GLfloat> val)
	{
		glUniform3f(this->location, val.x, val.y, val.z);
	}

	void ProgramLocation::setVec3fv(TVec3<GLfloat> *val, GLsizei count)
	{
		glUniform3fv(this->location, count, &val[0][0]);
	}

	void ProgramLocation::setVec4f(GLfloat val1, GLfloat val2, GLfloat val3, GLfloat val4)
	{
		glUniform4f(this->location, val1, val2, val3, val4);
	}

	void ProgramLocation::setVec4f(TVec4<GLfloat> val)
	{
		glUniform4f(this->location, val.x, val.y, val.z, val.w);
	}

	void ProgramLocation::setVec4fv(TVec4<GLfloat> *val, GLsizei count)
	{
		glUniform4fv(this->location, count, &val[0][0]);
	}

	void ProgramLocation::setMat3f(TMat3<GLfloat> val)
	{
		glUniformMatrix3fv(this->location, 1, GL_FALSE, &val[0][0]);
	}

	void ProgramLocation::setMat3fv(TMat3<GLfloat> *val, GLsizei count)
	{
		glUniformMatrix3fv(this->location, count, GL_FALSE, &val[0][0][0]);
	}

	void ProgramLocation::setMat4f(TMat4<GLfloat> val)
	{
		glUniformMatrix4fv(this->location, 1, GL_FALSE, &val[0][0]);
	}

	void ProgramLocation::setMat4fv(TMat4<GLfloat> *val, GLsizei count)
	{
		glUniformMatrix4fv(this->location, count, GL_FALSE, &val[0][0][0]);
	}

	void ProgramLocation::setVertexBuffer(VertexBuffer &buffer, GLint nb, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset)
	{
		buffer.bind(GL_ARRAY_BUFFER);
		glVertexAttribPointer(this->location, nb, type, normalized, stride, (void*)(unsigned long)offset);
	}

	void ProgramLocation::setVertexAttribArray(bool asArray)
	{
		if (asArray)
			glEnableVertexAttribArray(this->location);
		else
			glDisableVertexAttribArray(this->location);
	}

}
