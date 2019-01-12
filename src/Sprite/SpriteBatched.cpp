#include "SpriteBatched.h"
#include "../DrawableBuffers.h"
#include "./SpriteBatch.h"

namespace librender
{

	void SpriteBatched::setParent(DrawableBatch *parent)
	{
		if (this->parent && (!parent || reinterpret_cast<SpriteBatch*>(this->parent)->getTexture() != reinterpret_cast<SpriteBatch*>(parent)->getTexture()))
			requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_COLORS);
		DrawableBatched::setParent(parent);
	}

	Texture *SpriteBatched::getTexture()
	{
		if (this->parent)
			return reinterpret_cast<SpriteBatch*>(this->parent)->getTexture();
		return nullptr;
	}

}
