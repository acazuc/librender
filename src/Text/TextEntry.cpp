#include "Text.h"
#include <cstring>
#include <utf8.h>

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

#define VERTEX_BUFFER 0
#define TEX_COORD_BUFFER 1
#define COLOR_BUFFER 2

namespace librender
{

	TextEntry::TextEntry()
	: texCoords(NULL)
	, vertex(NULL)
	, colors(NULL)
	, shadowColor(Color::WHITE)
	, color(Color::WHITE)
	, verticesNumber(0)
	, charsNumber(0)
	, lineHeight(0)
	, updatesRequired(0)
	, shadowSize(0)
	, shadowX(0)
	, shadowY(0)
	, opacity(1)
	, scaleX(1)
	, scaleY(1)
	, x(0)
	, y(0)
	{
		//Empty
	}

	TextEntry::~TextEntry()
	{
		delete[] (this->vertex);
		delete[] (this->texCoords);
		delete[] (this->colors);
	}

	void TextEntry::fillTexCoords(GLfloat *texCoords)
	{
		char *iter = const_cast<char*>(this->text.c_str());
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t currentChar = utf8::next(iter, const_cast<char*>(this->text.c_str()) + this->text.length());
			getFont()->glArrayCharPart(currentChar, &texCoords[i * 8]);
		}
		if (this->shadowSize <= 0)
			return;
		uint16_t max;
		if (this->shadowSize == 1)
			max = 1;
		else
			max = (1 + (this->shadowSize - 1) * 2) * (1 + (this->shadowSize - 1) * 2) - 1 - 4 * (this->shadowSize - 1);
		for (uint32_t i = 0; i < max; ++i)
		{
			std::memcpy(&texCoords[this->charsNumber * 8 * (i + 1)], &texCoords[0], this->charsNumber * 8 * sizeof(*texCoords));
		}
	}

	void TextEntry::fillVertex(GLfloat *vertex)
	{
		int32_t shadowLen;
		if (this->shadowSize <= 0)
			shadowLen = 0;
		else if (this->shadowSize == 1)
		 	shadowLen = 1;
		else
			shadowLen = (1 + (this->shadowSize - 1) * 2) * (1 + (this->shadowSize - 1) * 2) - 1 - (this->shadowSize - 1) * 4;
		int32_t x = 0;
		int32_t y = 0;
		char *iter = const_cast<char*>(this->text.c_str());
		char *end = const_cast<char*>(this->text.c_str() + this->text.length());
		int32_t index = (shadowLen * this->charsNumber) * 8;
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t currentChar = utf8::next(iter, end);
			if (currentChar == '\n')
			{
				y += this->lineHeight * this->scaleY;
				x = 0;
			}
			else
			{
				FontGlyph *glyph = getFont()->getGlyph(currentChar);
				if (!glyph)
				{
					std::memset(&vertex[index], 0, 8 * sizeof(*this->vertex));
					index += 8;
					continue;
				}
				else
				{
					int32_t charWidth = glyph->getAdvance() * this->scaleX;
					int32_t charRenderWidth = glyph->getWidth() * this->scaleX;
					int32_t charRenderHeight = glyph->getHeight() * this->scaleY;
					int32_t charRenderX = x + glyph->getOffsetX();
					int32_t charRenderY = glyph->getOffsetY();
					vertex[index++] = charRenderX;
					vertex[index++] = charRenderY;
					vertex[index++] = charRenderX + charRenderWidth;
					vertex[index++] = charRenderY;
					vertex[index++] = charRenderX + charRenderWidth;
					vertex[index++] = charRenderY + charRenderHeight;
					vertex[index++] = charRenderX;
					vertex[index++] = charRenderY + charRenderHeight;
					x += charWidth * this->scaleX;
				}
			}
		}
		if (this->shadowSize <= 0)
			return;
		uint32_t tmp = 1 + (this->shadowSize - 1) * 2;
		uint8_t arrCount = 0;
		int32_t tmp2 = shadowLen * this->charsNumber * 8;
		for (uint8_t i = 0; i < tmp * tmp; ++i)
		{
			int8_t sx = i % tmp - (this->shadowSize - 1);
			int8_t sy = i / tmp - (this->shadowSize - 1);
			if (std::abs(sx) == std::abs(sy) && this->shadowSize != 1)
				continue;
			uint32_t index = this->charsNumber * 8 * arrCount;
			uint32_t add = 0;
			for (uint32_t j = 0; j < this->charsNumber * 4; ++j)
			{
				vertex[index + add] = vertex[tmp2 + add] + (sx + this->shadowX) * this->scaleX;
				++add;
				vertex[index + add] = vertex[tmp2 + add] + (sy + this->shadowY) * this->scaleY;
				++add;
			}
			arrCount++;
		}
	}

	void TextEntry::fillColors(GLfloat *colors)
	{
		int32_t shadowLen;
		if (this->shadowSize <= 0)
			shadowLen = 0;
		else if (this->shadowSize == 1)
		 	shadowLen = 1;
		else
			shadowLen = (1 + (this->shadowSize - 1) * 2) * (1 + (this->shadowSize - 1) * 2) - 1 - (this->shadowSize - 1) * 4;
		{
			float tab[4] = {this->color.getRed(), this->color.getGreen(), this->color.getBlue(), this->color.getAlpha() * this->opacity};
			int32_t tmp = (shadowLen * this->charsNumber * 4) * 4;
			for (uint32_t i = 0; i < this->charsNumber * 4; ++i)
			{
				std::memcpy(&colors[tmp], tab, sizeof(tab));
				tmp += 4;
			}
		}
		if (this->shadowSize <= 0)
			return;
		{
			float tab[4] = {this->shadowColor.getRed(), this->shadowColor.getGreen(), this->shadowColor.getBlue(), this->shadowColor.getAlpha() * this->opacity};
			for (uint32_t i = 0; i < this->charsNumber * 4; ++i)
				std::memcpy(&colors[i * 4], tab, sizeof(tab));
		}
		for (uint16_t i = 1; i < shadowLen; ++i)
			std::memcpy(&colors[this->charsNumber * 4 * 4 * i], &colors[0], this->charsNumber * 4 * 4 * sizeof(*colors));
	}

	void TextEntry::update()
	{
		if (!getFont())
			return;
		if (this->updatesRequired & UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & UPDATE_VERTEX)
			updateVertex();
		if (this->updatesRequired & UPDATE_COLORS)
			updateColors();
		this->updatesRequired = 0;
	}

	void TextEntry::resize(uint32_t len)
	{
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
		this->charsNumber = len;
		this->verticesNumber = this->charsNumber * 4;
		if (this->shadowSize > 0)
		{
			int16_t fac = 1;
			if (this->shadowSize > 0)
			{
				if (this->shadowSize == 1)
					fac += 1;
				else
					fac += (1 + (this->shadowSize - 1) * 2) * (1 + (this->shadowSize - 1) * 2) - 1 - 4 * (this->shadowSize - 1);
				if (fac < 1)
					fac = 1;
			}
			this->verticesNumber *= fac;
		}
		if (this->texCoords)
			delete[] (this->texCoords);
		this->texCoords = new GLfloat[this->verticesNumber * 2];
		if (this->vertex)
			delete[] (this->vertex);
		this->vertex = new GLfloat[this->verticesNumber * 2];
		if (this->colors)
			delete[] (this->colors);
		this->colors = new GLfloat[this->verticesNumber * 4];
	}

	void TextEntry::setText(std::string &text)
	{
		uint32_t newLen = utf8::distance(text.begin(), text.end());
		if (this->charsNumber != newLen)
			resize(newLen);
		this->text = text;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void TextEntry::setShadowColor(Color &color)
	{
		if (!color.compare(this->shadowColor))
			return;
		this->shadowColor = color;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void TextEntry::setColor(Color &color)
	{
		if (!color.compare(this->color))
			return;
		this->color = color;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void TextEntry::setShadowSize(int16_t shadowSize)
	{
		if (this->shadowSize == shadowSize)
			return;
		this->shadowSize = shadowSize;
		resize(this->charsNumber);
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void TextEntry::setShadowX(int16_t shadowX)
	{
		if (this->shadowX == shadowX)
			return;
		this->shadowX = shadowX;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void TextEntry::setShadowY(int16_t shadowY)
	{
		if (this->shadowY == shadowY)
			return;
		this->shadowY = shadowY;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void TextEntry::setOpacity(float opacity)
	{
		if (this->opacity == opacity)
			return;
		this->opacity = opacity;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void TextEntry::setScaleX(float scaleX)
	{
		if (this->scaleX == scaleX)
			return;
		this->scaleX = scaleX;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void TextEntry::setScaleY(float scaleY)
	{
		if (this->scaleY == scaleY)
			return;
		this->scaleY = scaleY;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void TextEntry::setScale(float scale)
	{
		setScaleX(scale);
		setScaleY(scale);
	}

}
