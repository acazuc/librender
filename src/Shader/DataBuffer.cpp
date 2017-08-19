#include "DataBuffer.h"

namespace librender
{

	DataBuffer::DataBuffer()
	{
		glGenBuffers(1, &this->id);
	}

	DataBuffer::~DataBuffer()
	{
		glDeleteBuffers(1, &this->id);
	}

	void DataBuffer::setData(GLenum bufType, const void *data, GLsizei len, GLenum type, GLsizei stride, GLenum usage)
	{
		bind(bufType);
		glBufferData(bufType, len, data, usage);
		this->type = type;
		this->stride = stride;
	}
	
	void DataBuffer::bind(GLenum type)
	{
		glBindBuffer(type, this->id);
	}

}
