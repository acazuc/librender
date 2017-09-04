#include "VertexBuffer.h"

namespace librender
{

	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &this->id);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &this->id);
	}

	void VertexBuffer::setData(GLenum bufType, const void *data, GLsizei len, GLenum type, GLsizei stride, GLenum usage)
	{
		bind(bufType);
		glBufferData(bufType, len, data, usage);
		this->type = type;
		this->stride = stride;
	}
	
	void VertexBuffer::bind(GLenum type)
	{
		glBindBuffer(type, this->id);
	}

}
