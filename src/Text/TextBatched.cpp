#include "./TextBatched.h"
#include "../DrawableBuffers.h"
#include "./TextBatch.h"

namespace librender
{

	void TextBatched::setParent(DrawableBatch *parent)
	{
		if (this->parent && (!parent || reinterpret_cast<TextBatch*>(this->parent)->getFont() != reinterpret_cast<TextBatch*>(parent)->getFont()))
			requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_COLORS);
		DrawableBatched::setParent(parent);
	}

	Font *TextBatched::getFont()
	{
		if (this->parent)
			return reinterpret_cast<TextBatch*>(this->parent)->getFont();
		return nullptr;
	}

}
