#include "TextBatch.h"
#include "../DrawableBuffers.h"
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
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES);
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			TextBatched *child = reinterpret_cast<TextBatched*>(this->childs[i]);
			child->addChanges(DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES);
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
