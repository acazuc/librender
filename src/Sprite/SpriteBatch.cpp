#include "SpriteBatch.h"
#include "../DrawableUpdate.h"
#include "./SpriteBatched.h"
#include "../GL.h"

namespace librender
{

	SpriteBatch::SpriteBatch()
	: texture(nullptr)
	{
	}

	void SpriteBatch::draw()
	{
		if (!update())
			return;
		if (this->texture)
			this->texture->bind();
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		DrawableBatch::draw();
	}

	void SpriteBatch::setTexture(Texture *texture)
	{
		this->texture = texture;
	}

}
