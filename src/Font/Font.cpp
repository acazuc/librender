#include "Font.h"
#include "../GL.h"
#include "utf8.h"
#include <cstdlib>
#include <cstring>
#include <cmath>

namespace librender
{

	Font::Font(FontModel *parent, FT_Face ftFace, int size)
	{
		this->parent = parent;
		this->ftFace = ftFace;
		if (FT_Set_Pixel_Sizes(this->ftFace, 0, size))
			throw std::exception();
		this->glyphs = new FontGlyph*[LIBRENDER_FONT_MODEL_CHARS_NUMBER];
		std::memset(this->glyphs, 0, LIBRENDER_FONT_MODEL_CHARS_NUMBER * sizeof(*this->glyphs));
		this->glyphs_datas = new char*[LIBRENDER_FONT_MODEL_CHARS_NUMBER];
		loadList(size);
		createSet();
		delete[] (this->glyphs_datas);
	}

	Font::~Font()
	{
		for (uint32_t i = 0; i < LIBRENDER_FONT_MODEL_CHARS_NUMBER; ++i)
			delete (this->glyphs[i]);
		delete[] (this->glyphs);
	}
	
	void Font::bind()
	{
		this->texture.bind();
	}

	void Font::loadList(int size)
	{
		for (uint32_t i = 0; i < LIBRENDER_FONT_MODEL_CHARS_NUMBER; ++i)
		{
			if (!this->parent->isAvailable(i))
				continue;
			if (FT_Load_Char(this->ftFace, i, FT_LOAD_RENDER))
				continue;
			this->glyphs[i] = new FontGlyph(this->ftFace->glyph->advance.x >> 6, this->ftFace->glyph->bitmap.width, this->ftFace->glyph->bitmap.rows
				, this->ftFace->glyph->bitmap_left, size - this->ftFace->glyph->bitmap_top);
			this->glyphs_datas[i] = new char[this->glyphs[i]->getWidth() * this->glyphs[i]->getHeight()];
			std::memcpy(this->glyphs_datas[i], this->ftFace->glyph->bitmap.buffer, this->glyphs[i]->getWidth() * this->glyphs[i]->getHeight());
		}
	}

	void Font::createSet()
	{
		uint32_t totalWidth = 0;
		int32_t maxHeight = 0;
		uint32_t maxWidth = 0;
		for (uint32_t i = 0; i < LIBRENDER_FONT_MODEL_CHARS_NUMBER; ++i)
		{
			FontGlyph *glyph = this->glyphs[i];
			if (!glyph)
				continue;
			totalWidth += glyph->getWidth() + 1;
			if (glyph->getHeight() + glyph->getOffsetY() > maxHeight)
				maxHeight = glyph->getHeight() + glyph->getOffsetY();
			if (glyph->getWidth() > maxWidth)
				maxWidth = glyph->getWidth() + 1;
		}
		this->height = maxHeight;
		uint32_t size = std::sqrt(totalWidth * (maxHeight + 2)) + maxWidth + maxHeight + 4;
		char *data = new char[size * size * 4];
		std::memset(data, 0, size * size * 4);
		uint32_t x = 1;
		uint32_t y = 1;
		uint32_t lineHeight = 0;
		for (uint32_t i = 0; i < LIBRENDER_FONT_MODEL_CHARS_NUMBER; ++i)
		{
			FontGlyph *glyph = this->glyphs[i];
			if (!glyph)
				continue;
			if (x + glyph->getWidth() + 2 >= size)
			{
				x = 1;
				y += lineHeight + 1;
				lineHeight = 0;
			}
			glyph->setTexX(x);
			glyph->setTexY(y);
			if (glyph->getHeight() > lineHeight)
				lineHeight = glyph->getHeight();
			copyChar(x, y, data, size, glyph, this->glyphs_datas[i]);
			delete[] (this->glyphs_datas[i]);
			x += glyph->getWidth() + 1;
		}
		if (x == 1)
			y -= lineHeight + 1;
		data = imageCrop(data, size, y + lineHeight + 1);
		buildGLTexture(data, size, y + lineHeight + 1);
		delete[] (data);
	}

	char *Font::imageCrop(char *data, int32_t size, int32_t height)
	{
		if (height < size)
		{
			this->textureWidth = size;
			this->textureHeight = height;
			char *tmp = new char[size * height * 4];
			std::memcpy(tmp, data, size * height * 4);
			delete[] (data);
			return (tmp);
		}
		this->textureWidth = size;
		this->textureHeight = size;
		return (data);
	}

	void Font::copyChar(int32_t x, int32_t y, char *data, uint32_t size, FontGlyph *glyph, char *glyph_data)
	{
		for (uint32_t tY = 0; tY < glyph->getHeight(); ++tY)
		{
			for (uint32_t tX = 0; tX < glyph->getWidth(); ++tX)
			{
				reinterpret_cast<int*>(data)[((y + tY) * size + x + tX)] = 0xffffff | (glyph_data[tY * glyph->getWidth() + tX] << 24);
			}
		}
	}

	void Font::buildGLTexture(char *data, uint32_t width, uint32_t height)
	{
		this->texture.bind();
		this->texture.setFilter(TEXTURE_FILTER_LINEAR, TEXTURE_FILTER_LINEAR);
		this->texture.setWrap(TEXTURE_WRAP_CLAMP_TO_BORDER, TEXTURE_WRAP_CLAMP_TO_BORDER);
		this->texture.setData(data, width, height);
	}

	FontGlyph *Font::getGlyph(uint32_t character)
	{
		if (character >= LIBRENDER_FONT_MODEL_CHARS_NUMBER || !this->glyphs[character])
		{
			if (character == '?')
				return (NULL);
			return (getGlyph('?'));
		}
		return (this->glyphs[character]);
	}

	int32_t Font::getWidth(std::string &text)
	{
		uint32_t maxWidth = 0;
		uint32_t currentWidth = 0;
		char *iter = const_cast<char*>(text.c_str());
		char *end = iter + text.length();
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
				FontGlyph *glyph = getGlyph(currentChar);
				if (glyph)
					currentWidth += glyph->getAdvance();
			}
		}
		if (currentWidth > maxWidth)
			maxWidth = currentWidth;
		return (maxWidth);
	}

	int32_t Font::getHeight(std::string &text)
	{
		uint32_t nlNb = 1;
		size_t pos = 0;
		while ((pos = text.find('\n', pos)) != std::string::npos)
		{
			++pos;
			++nlNb;
		}
		return (this->height * nlNb);
	}

	void Font::drawQuad(float x, float y, float width, float height, int texX, int texY, int texWidth, int texHeight)
	{
		float textureSrcX = static_cast<float>(texX) / this->textureWidth;
		float textureSrcY = static_cast<float>(texY) / this->textureHeight;
		float renderWidth = static_cast<float>(texWidth) / this->textureWidth;
		float renderHeight = static_cast<float>(texHeight) / this->textureHeight;
		glTexCoord2f(textureSrcX, textureSrcY);
		glVertex2f(x, y);
		glTexCoord2f(textureSrcX, textureSrcY + renderHeight);
		glVertex2f(x, y + height);
		glTexCoord2f(textureSrcX + renderWidth, textureSrcY + renderHeight);
		glVertex2f(x + width, y + height);
		glTexCoord2f(textureSrcX + renderWidth, textureSrcY);
		glVertex2f(x + width, y);
	}

	void Font::glArrayQuad(int texX, int texY, int texWidth, int texHeight, float *texCoords)
	{
		float textureSrcX = static_cast<float>(texX) / this->textureWidth;
		float textureSrcY = static_cast<float>(texY) / this->textureHeight;
		float renderWidth = static_cast<float>(texWidth) / this->textureWidth;
		float renderHeight = static_cast<float>(texHeight) / this->textureHeight;
		texCoords[0] = textureSrcX;
		texCoords[1] = textureSrcY;
		texCoords[2] = textureSrcX + renderWidth;
		texCoords[3] = textureSrcY;
		texCoords[4] = textureSrcX + renderWidth;
		texCoords[5] = textureSrcY + renderHeight;
		texCoords[6] = textureSrcX;
		texCoords[7] = textureSrcY + renderHeight;
	}

	void Font::glChar(uint32_t character, float *texCoords)
	{
		glGlyph(getGlyph(character), texCoords);
	}

	void Font::glGlyph(FontGlyph *glyph, float *texCoords)
	{
		if (!glyph)
		{
			std::memset(texCoords, 0, 8 * sizeof(*texCoords));
			return;
		}
		glArrayQuad(glyph->getTexX(), glyph->getTexY(), glyph->getWidth(), glyph->getHeight(), texCoords);
	}

}
