#include "TextTessellator.h"
#include "../GL.h"

namespace librender
{

	TextTessellator::TextTessellator(Context &context)
	: DrawableTessellator(context)
	, font(nullptr)
	{
	}

	void TextTessellator::draw()
	{
		if (!this->font)
			return;
		this->font->bind();
		DrawableTessellator::draw();
	}

	void TextTessellator::addGlyph(Glyph *glyph, Vec2 pos, Vec4 color)
	{
		if (!this->font)
			return;
		if (!glyph)
			return;
		Vec2 tmp[4];
		this->font->glGlyph(glyph, &tmp[0].x);
		Vec2 org(pos);
		Vec2 dst(pos + Vec2(glyph->getWidth(), glyph->getHeight()));
		uint32_t base = this->vertexes.size();
		addPoint(Vec2(org.x, org.y), tmp[0], color);
		addPoint(Vec2(dst.x, org.y), tmp[1], color);
		addPoint(Vec2(dst.x, dst.y), tmp[2], color);
		addPoint(Vec2(org.x, dst.y), tmp[3], color);
		addIndice(base + 0);
		addIndice(base + 3);
		addIndice(base + 1);
		addIndice(base + 2);
		addIndice(base + 1);
		addIndice(base + 3);
	}

	void TextTessellator::addChar(uint32_t character, Vec2 pos, Vec4 color)
	{
		if (!this->font)
			return;
		addGlyph(this->font->getGlyph(character), pos, color);
	}

}
