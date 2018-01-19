#include "TextTessellator.h"
#include "../GL.h"
#include <utf8.h>

namespace librender
{

	TextTessellator::TextTessellator()
	: font(NULL)
	{
		//Empty
	}

	void TextTessellator::clear()
	{
		std::vector<Vec2> emptyTexCoords;
		std::vector<Vec2> emptyVertexes;
		std::vector<Vec4> emptyColors;
		this->texCoords.swap(emptyTexCoords);
		this->vertexes.swap(emptyVertexes);
		this->colors.swap(emptyColors);
	}

	void TextTessellator::draw()
	{
		if (!this->font)
			return;
		this->font->bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors.data());
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes.data());
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords.data());
		glDrawArrays(GL_QUADS, 0, this->texCoords.size());
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void TextTessellator::add(Vec2 vertex, Vec2 texCoords, Vec4 color)
	{
		this->texCoords.push_back(texCoords);
		this->vertexes.push_back(vertex);
		this->colors.push_back(color);
	}

	void TextTessellator::addGlyph(FontGlyph *glyph, Vec2 pos, Vec4 color)
	{
		if (!this->font)
			return;
		if (!glyph)
			return;
		Vec2 tmp[8];
		this->font->glGlyph(glyph, &tmp[0].x);
		Vec2 org(pos);
		Vec2 dst(pos + Vec2(glyph->getWidth(), glyph->getHeight()));
		add(Vec2(org.x, org.y), tmp[0], color);
		add(Vec2(dst.x, org.y), tmp[1], color);
		add(Vec2(dst.x, dst.y), tmp[2], color);
		add(Vec2(org.x, dst.y), tmp[3], color);
	}

	void TextTessellator::addChar(uint32_t character, Vec2 pos, Vec4 color)
	{
		if (!this->font)
			return;
		addGlyph(this->font->getGlyph(character), pos, color);
	}

}
