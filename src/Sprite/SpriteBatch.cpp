#include "SpriteBatch.h"
#include "../DrawableBuffers.h"
#include "./SpriteBatched.h"

namespace librender
{

	SpriteBatch::SpriteBatch(Context &context)
	: DrawableBatch(context)
	, texture(nullptr)
	{
	}

	void SpriteBatch::draw()
	{
		if (!update())
			return;
		this->context.setSamplerTexture(0, this->texture);
		DrawableBatch::draw();
	}

	void SpriteBatch::setTexture(Texture *texture)
	{
		if (this->texture == texture)
			return;
		this->texture = texture;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS);
	}

}
