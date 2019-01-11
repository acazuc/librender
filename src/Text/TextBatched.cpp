#include "./TextBatched.h"
#include "../DrawableUpdate.h"
#include "./TextBatch.h"

namespace librender
{

	void TextBatched::setParent(DrawableBatch *parent)
	{
		if (this->parent && (!parent || reinterpret_cast<TextBatch*>(this->parent)->getFont() != reinterpret_cast<TextBatch*>(parent)->getFont()))
			requireUpdates(DRAWABLE_UPDATE_VERTEXES | DRAWABLE_UPDATE_TEX_COORDS | DRAWABLE_UPDATE_COLORS);
		DrawableBatched::setParent(parent);
	}

	Font *TextBatched::getFont()
	{
		if (this->parent)
			return reinterpret_cast<TextBatch*>(this->parent)->getFont();
		return nullptr;
	}

}
