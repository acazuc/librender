#include "Text.h"
#include "../DrawableBuffers.h"
#include "../GL.h"

namespace librender
{

	Text::Text(Context &context)
	: Drawable(context)
	, font(nullptr)
	, lastVerticesNumber(0)
	{
		requireUpdates(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_COLORS | DRAWABLE_BUFFER_VERTEXES);
	}

	void Text::draw()
	{
		if (!this->font)
			return;
		updateBuffers();
		this->font->bind();
		Drawable::draw();
	}

	void Text::setFont(Font *font)
	{
		if (this->font == font)
			return;
		this->font = font;
		this->lineHeight = this->font->getLineHeight();
		requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS);
		recalcWidth();
		recalcHeight();
	}

}
