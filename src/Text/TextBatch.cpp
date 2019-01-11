#include "TextBatch.h"
#include "../DrawableUpdate.h"
#include "./TextBatched.h"
#include "../GL.h"

namespace librender
{

	TextBatch::TextBatch()
	: font(nullptr)
	{
	}

	void TextBatch::draw()
	{
		if (!this->font)
			return;
		if (!update())
			return;
		this->font->bind();
		DrawableBatch::draw();
	}

	void TextBatch::setFont(Font *font)
	{
		this->font = font;
		requireUpdates(DRAWABLE_UPDATE_TEX_COORDS | DRAWABLE_UPDATE_VERTEXES);
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			TextBatched *child = reinterpret_cast<TextBatched*>(this->childs[i]);
			child->addChanges(DRAWABLE_UPDATE_TEX_COORDS | DRAWABLE_UPDATE_VERTEXES);
			child->recalcWidth();
			child->recalcHeight();
		}
	}

	int32_t TextBatch::getLineHeight()
	{
		if (!this->font)
			return 0;
		return this->font->getLineHeight();
	}

}
