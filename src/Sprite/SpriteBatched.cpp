#include "SpriteBatched.h"
#include "../DrawableBuffers.h"
#include "./SpriteBatch.h"

namespace librender
{

	void SpriteBatched::setParent(DrawableBatch *parent)
	{
		DrawableBatched::setParent(parent);
	}

	Texture *SpriteBatched::getTexture()
	{
		if (this->parent)
			return reinterpret_cast<SpriteBatch*>(this->parent)->getTexture();
		return nullptr;
	}

}
