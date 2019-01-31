#include "SpriteBatch.h"
#include "../DrawableBuffers.h"
#include "./SpriteBatched.h"
#include "../GL.h"

namespace librender
{

	SpriteBatch::SpriteBatch(Context *context)
	: DrawableBatch(context)
	, texture(nullptr)
	{
	}

	void SpriteBatch::draw()
	{
		if (!update())
			return;
		if (this->texture)
		{
			this->buffers |= DRAWABLE_BUFFER_TEX_COORDS;
			this->texture->bind();
		}
		else
		{
			this->buffers &= ~DRAWABLE_BUFFER_TEX_COORDS;
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		DrawableBatch::draw();
	}

	void SpriteBatch::setTexture(Texture *texture)
	{
		this->texture = texture;
	}

}
