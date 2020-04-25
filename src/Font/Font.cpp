#include "Font.h"
#include "../GL.h"
#include <libunicode/utf8.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cstring>

namespace librender
{

	Font::Font(FontModel &parent, uint32_t size, bool alphaTexture)
	: parent(parent)
	, atlas(alphaTexture)
	, lastAtlasRevision(0)
	, revision(1)
	, height(0)
	, size(size)
	{
		this->texture.bind();
		this->texture.setFilter(TEXTURE_FILTER_LINEAR, TEXTURE_FILTER_LINEAR);
		this->texture.setWrap(TEXTURE_WRAP_CLAMP_TO_BORDER, TEXTURE_WRAP_CLAMP_TO_BORDER);
		if (!this->parent.setSize(this->size))
			throw std::exception();
		this->height = this->parent.getFtFace()->size->metrics.height >> 6;
		if (this->height > 2)
			this->height -= 2;
	}

	Font::~Font()
	{
	}
	
	void Font::bind()
	{
		this->texture.bind();
	}

	Glyph *Font::loadGlyph(uint32_t codepoint)
	{
		if (!this->parent.setSize(this->size))
			return nullptr;
		if (codepoint < 0x1f) /* control code */
			return nullptr;
		uint32_t index = FT_Get_Char_Index(this->parent.getFtFace(), codepoint);
		if (!index)
			return nullptr;
		if (FT_Load_Glyph(this->parent.getFtFace(), index, FT_LOAD_DEFAULT))
			return nullptr;
		if (!this->parent.getFtFace()->glyph->advance.x)
			return nullptr;
		if (FT_Render_Glyph(this->parent.getFtFace()->glyph, FT_RENDER_MODE_NORMAL))
			return nullptr;
		Glyph glyph(this->parent.getFtFace()->glyph->advance.x >> 6, \
				this->parent.getFtFace()->glyph->bitmap.width, this->parent.getFtFace()->glyph->bitmap.rows, \
				this->parent.getFtFace()->glyph->bitmap_left, this->size - this->parent.getFtFace()->glyph->bitmap_top);
		uint32_t glyphX;
		uint32_t glyphY;
		if (this->atlas.findPlace(glyph.getWidth() + 1, glyph.getHeight() + 1, &glyphX, &glyphY))
		{
			glyph.setTexX(glyphX + 1);
			glyph.setTexY(glyphY + 1);
			return this->atlas.addGlyph(glyphX + 1, glyphY + 1, codepoint, glyph, this->parent.getFtFace()->glyph->bitmap.buffer);
		}
		this->atlas.grow();
		if (this->atlas.findPlace(glyph.getWidth() + 1, glyph.getHeight() + 1, &glyphX, &glyphY))
		{
			glyph.setTexX(glyphX + 1);
			glyph.setTexY(glyphY + 1);
			return this->atlas.addGlyph(glyphX + 1, glyphY + 1, codepoint, glyph, this->parent.getFtFace()->glyph->bitmap.buffer);
		}
		glyph.setWidth(0);
		glyph.setHeight(0);
		glyph.setTexX(0);
		glyph.setTexY(0);
		return this->atlas.addGlyph(0, 0, codepoint, glyph, nullptr);
	}

	int32_t Font::getWidth(const std::string &text)
	{
		uint32_t maxWidth = 0;
		uint32_t currentWidth = 0;
		const char *iter = text.c_str();
		const char *end = iter + text.length();
		while (iter != end)
		{
			uint32_t currentChar = utf8::next(iter, end);
			if (currentChar == '\n')
			{
				if (currentWidth > maxWidth)
					maxWidth = currentWidth;
				currentWidth = 0;
			}
			else
			{
				Glyph *glyph = getGlyph(currentChar);
				if (glyph)
					currentWidth += glyph->getAdvance();
			}
		}
		if (currentWidth > maxWidth)
			maxWidth = currentWidth;
		return maxWidth;
	}

	int32_t Font::getHeight(const std::string &text)
	{
		uint32_t nlNb = 1;
		size_t pos = 0;
		while ((pos = text.find('\n', pos)) != std::string::npos)
		{
			++pos;
			++nlNb;
		}
		return this->height * nlNb;
	}

	void Font::glUpdate()
	{
		if (this->atlas.getRevision() == this->lastAtlasRevision)
			return;
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, this->atlas.isAlphaTexture() ? GL_ALPHA : GL_RGBA, this->atlas.getWidth(), this->atlas.getHeight(), 0, this->atlas.isAlphaTexture() ? GL_ALPHA : GL_RGBA, GL_UNSIGNED_BYTE, this->atlas.getData());
		this->revision++;
	}

	void Font::glArrayQuad(int32_t texX, int32_t texY, int32_t texWidth, int32_t texHeight, float *texCoords)
	{
		float textureSrcX = static_cast<float>(texX) / this->atlas.getWidth();
		float textureSrcY = static_cast<float>(texY) / this->atlas.getHeight();
		float renderWidth = static_cast<float>(texWidth) / this->atlas.getWidth();
		float renderHeight = static_cast<float>(texHeight) / this->atlas.getHeight();
		texCoords[0] = textureSrcX;
		texCoords[1] = textureSrcY;
		texCoords[2] = textureSrcX + renderWidth;
		texCoords[3] = textureSrcY;
		texCoords[4] = textureSrcX + renderWidth;
		texCoords[5] = textureSrcY + renderHeight;
		texCoords[6] = textureSrcX;
		texCoords[7] = textureSrcY + renderHeight;
	}

	Glyph *Font::getGlyph(uint32_t codepoint)
	{
		Glyph *glyph = this->atlas.getGlyph(codepoint);
		if (glyph)
			return glyph;
		glyph = loadGlyph(codepoint);
		if (glyph)
			return glyph;
		Glyph tmp(0, 0, 0, 0, 0);
		tmp.setTexX(0);
		tmp.setTexY(0);
		return this->atlas.addGlyph(0, 0, codepoint, tmp, nullptr);
	}

	void Font::glChar(uint32_t codepoint, float *texCoords)
	{
		glGlyph(getGlyph(codepoint), texCoords);
	}

	void Font::glGlyph(Glyph *glyph, float *texCoords)
	{
		if (!glyph)
		{
			std::memset(texCoords, 0, 8 * sizeof(*texCoords));
			return;
		}
		glArrayQuad(glyph->getTexX(), glyph->getTexY(), glyph->getWidth(), glyph->getHeight(), texCoords);
	}

}
