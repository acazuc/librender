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

	void DataBuffer::setData(const void *data, uint64_t len, GLenum usage)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, len, data, usage);
	}
	
	void DataBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->id);
	}

}
