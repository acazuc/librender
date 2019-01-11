#include "SpriteBatched.h"
#include "../DrawableUpdate.h"
#include "./SpriteBatch.h"

namespace librender
{

	void SpriteBatched::setParent(DrawableBatch *parent)
	{
		if (this->parent && (!parent || reinterpret_cast<SpriteBatch*>(this->parent)->getTexture() != reinterpret_cast<SpriteBatch*>(parent)->getTexture()))
			requireUpdates(DRAWABLE_UPDATE_VERTEXES | DRAWABLE_UPDATE_TEX_COORDS | DRAWABLE_UPDATE_COLORS);
		DrawableBatched::setParent(parent);
	}

	Texture *SpriteBatched::getTexture()
	{
		if (this->parent)
			return reinterpret_cast<SpriteBatch*>(this->parent)->getTexture();
		return nullptr;
	}

}
