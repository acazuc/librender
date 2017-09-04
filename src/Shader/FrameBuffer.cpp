#include "FrameBuffer.h"

namespace librender
{

	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &this->id);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &this->id);
	}

	void FrameBuffer::attachTexture(GLenum attachment, Texture &texture, GLint level)
	{
		bind();
		//glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture.getId(), level);
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	}

}
