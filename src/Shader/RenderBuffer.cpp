#include "RenderBuffer.h"

namespace librender
{

	RenderBuffer::RenderBuffer()
	{
		glGenRenderbuffers(1, &this->id);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &this->id);
	}

	void RenderBuffer::bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, this->id);
	}

}
