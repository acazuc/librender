#include "TextEntry.h"
#include "./TextUpdate.h"
#include <cstring>
#include <utf8.h>

namespace librender
{

	TextEntry::TextEntry()
	: shadowColor(Color::BLACK)
	, color(Color::WHITE)
	, texCoords(NULL)
	, vertexes(NULL)
	, colors(NULL)
	, scale(1)
	, pos(0)
	, verticesNumber(0)
	, charsNumber(0)
	, updatesRequired(0)
	, shadowSize(0)
	, lineHeight(-1)
	, maxWidth(-1)
	, shadowX(0)
	, shadowY(0)
	, height(0)
	, width(0)
	, opacity(1)
	, mustCalcHeight(false)
	, mustCalcWidth(false)
	{
		//Empty
	}

	TextEntry::~TextEntry()
	{
		delete[] (this->texCoords);
		delete[] (this->vertexes);
		delete[] (this->colors);
	}

	void TextEntry::fillTexCoords(Vec2 *texCoords)
	{
		char *iter = const_cast<char*>(this->text.c_str());
		char *end = iter + this->text.length();
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t character = utf8::next(iter, end);
			getFont()->glChar(character, reinterpret_cast<float*>(&texCoords[i * 4]));
		}
		if (this->shadowSize <= 0)
			return;
		uint16_t max;
		if (this->shadowSize == 1)
		{
			max = 1;
		}
		else
		{
			int16_t tmp = this->shadowSize - 1;
			int16_t tmp2 = 1 + tmp * 2;
			max = tmp2 * tmp2 - 1 - 4 * tmp;
		}
		for (uint32_t i = 0; i < max; ++i)
			std::memcpy(&texCoords[this->charsNumber * 4 * (i + 1)], &texCoords[0], this->charsNumber * 4 * sizeof(*texCoords));
	}

	void TextEntry::fillVertexes(Vec2 *vertexes)
	{
		int32_t shadowLen;
		if (this->shadowSize <= 0)
		{
			shadowLen = 0;
		}
		else if (this->shadowSize == 1)
		{
		 	shadowLen = 1;
		}
		else
		{
			int16_t tmp = this->shadowSize - 1;
			int16_t tmp2 = 1 + tmp * 2;
			shadowLen = tmp2 * tmp2 - 1 - 4 * tmp;
		}
		float x = 0;
		float y = 0;
		char *iter = const_cast<char*>(this->text.c_str());
		char *end = iter + this->text.length();
		int32_t index = (shadowLen * this->charsNumber) * 4;
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t character = utf8::next(iter, end);
			if (character == '\n')
			{
				y += getLineHeight();
				x = 0;
				std::memset(&vertexes[index], 0, 4 * sizeof(*this->vertexes));
				index += 4;
				continue;
			}
			FontGlyph *glyph = getFont()->getGlyph(character);
			if (!glyph)
			{
				std::memset(&vertexes[index], 0, 4 * sizeof(*this->vertexes));
				index += 4;
				continue;
			}
			else
			{
				float charWidth = glyph->getAdvance();
				float charRenderWidth = glyph->getWidth();
				float charRenderHeight = glyph->getHeight();
				float charRenderX = x + glyph->getOffsetX();
				float charRenderY = y + glyph->getOffsetY();
				vertexes[index].x = charRenderX;
				vertexes[index].y = charRenderY;
				++index;
				vertexes[index].x = charRenderX + charRenderWidth;
				vertexes[index].y = charRenderY;
				++index;
				vertexes[index].x = charRenderX + charRenderWidth;
				vertexes[index].y = charRenderY + charRenderHeight;
				++index;
				vertexes[index].x = charRenderX;
				vertexes[index].y = charRenderY + charRenderHeight;
				++index;
				x += charWidth;
			}
			if (this->maxWidth > 0 && x >= this->maxWidth)
			{
				y += getLineHeight();
				x = 0;
			}
		}
		if (this->shadowSize <= 0)
			return;
		uint32_t tmp = 1 + (this->shadowSize - 1) * 2;
		uint8_t arrCount = 0;
		int32_t tmp2 = shadowLen * this->charsNumber * 4;
		for (uint8_t i = 0; i < tmp * tmp; ++i)
		{
			int8_t sx = i % tmp - (this->shadowSize - 1);
			int8_t sy = i / tmp - (this->shadowSize - 1);
			if (std::abs(sx) == std::abs(sy) && this->shadowSize != 1)
				continue;
			uint32_t index = this->charsNumber * 4 * arrCount;
			Vec2 vtmp(this->shadowX + sx, this->shadowY + sy);
			for (uint32_t j = 0; j < this->charsNumber * 4; ++j)
				vertexes[index + j] = vertexes[tmp2 + j] + vtmp;
			arrCount++;
		}
	}

	void TextEntry::fillColors(Vec4 *colors)
	{
		int32_t shadowLen;
		if (this->shadowSize <= 0)
		{
			shadowLen = 0;
		}
		else if (this->shadowSize == 1)
		{
		 	shadowLen = 1;
		}
		else
		{
			int16_t tmp = this->shadowSize - 1;
			int16_t tmp2 = 1 + tmp * 2;
			shadowLen = tmp2 * tmp2 - 1 - 4 * tmp;
		}
		{
			float tab[4] = {this->color.getRed(), this->color.getGreen(), this->color.getBlue(), this->color.getAlpha() * this->opacity};
			int32_t tmp = shadowLen * this->charsNumber * 4;
			for (uint32_t i = 0; i < this->charsNumber * 4; ++i)
			{
				std::memcpy(&colors[tmp], tab, sizeof(tab));
				++tmp;
			}
		}
		if (this->shadowSize <= 0)
			return;
		{
			float tab[4] = {this->shadowColor.getRed(), this->shadowColor.getGreen(), this->shadowColor.getBlue(), this->shadowColor.getAlpha() * this->opacity};
			for (uint32_t i = 0; i < this->charsNumber * 4; ++i)
				std::memcpy(&colors[i], tab, sizeof(tab));
		}
		for (uint16_t i = 1; i < shadowLen; ++i)
			std::memcpy(&colors[this->charsNumber * 4 * i], &colors[0], this->charsNumber * 4 * sizeof(*colors));
	}

	void TextEntry::update()
	{
		if (!getFont())
			return;
		if (this->updatesRequired & TEXT_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & TEXT_UPDATE_VERTEXES)
			updateVertexes();
		if (this->updatesRequired & TEXT_UPDATE_COLORS)
			updateColors();
		this->updatesRequired = 0;
	}

	void TextEntry::resize(uint32_t len)
	{
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= TEXT_UPDATE_TEX_COORDS;
		this->updatesRequired |= TEXT_UPDATE_COLORS;
		this->charsNumber = len;
		this->verticesNumber = this->charsNumber * 4;
		if (this->shadowSize > 0)
		{
			int16_t fac = 1;
			if (this->shadowSize > 0)
			{
				if (this->shadowSize == 1)
				{
					fac += 1;
				}
				else
				{
					int16_t tmp = this->shadowSize - 1;
					int16_t tmp2 = 1 + tmp * 2;
					fac += tmp2 * tmp2 - 1 - 4 * tmp;
				}
				if (fac < 1)
					fac = 1;
			}
			this->verticesNumber *= fac;
		}
		delete[] (this->texCoords);
		this->texCoords = new Vec2[std::max(1u, this->verticesNumber)];
		delete[] (this->vertexes);
		this->vertexes = new Vec2[std::max(1u, this->verticesNumber)];
		delete[] (this->colors);
		this->colors = new Vec4[std::max(1u, this->verticesNumber)];
	}

	void TextEntry::setText(std::string &text)
	{
		recalcWidth();
		recalcHeight();
		uint32_t newLen = utf8::distance(text.begin(), text.end());
		if (this->charsNumber != newLen)
			resize(newLen);
		this->text = text;
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= TEXT_UPDATE_TEX_COORDS;
	}

	void TextEntry::setShadowColor(Color &color)
	{
		if (!color.compare(this->shadowColor))
			return;
		this->shadowColor = color;
		this->updatesRequired |= TEXT_UPDATE_COLORS;
	}

	void TextEntry::setColor(Color &color)
	{
		if (!color.compare(this->color))
			return;
		this->color = color;
		this->updatesRequired |= TEXT_UPDATE_COLORS;
	}

	void TextEntry::setShadowSize(int16_t shadowSize)
	{
		if (this->shadowSize == shadowSize)
			return;
		this->shadowSize = shadowSize;
		resize(this->charsNumber);
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= TEXT_UPDATE_TEX_COORDS;
		this->updatesRequired |= TEXT_UPDATE_COLORS;
	}

	void TextEntry::setShadowX(int32_t shadowX)
	{
		if (this->shadowX == shadowX)
			return;
		this->shadowX = shadowX;
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
	}

	void TextEntry::setShadowY(int32_t shadowY)
	{
		if (this->shadowY == shadowY)
			return;
		this->shadowY = shadowY;
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
	}

	void TextEntry::setOpacity(float opacity)
	{
		if (this->opacity == opacity)
			return;
		this->opacity = opacity;
		this->updatesRequired |= TEXT_UPDATE_COLORS;
	}

	void TextEntry::setScaleX(float scaleX)
	{
		if (this->scale.x == scaleX)
			return;
		this->scale.x = scaleX;
	}

	void TextEntry::setScaleY(float scaleY)
	{
		if (this->scale.y == scaleY)
			return;
		this->scale.y = scaleY;
	}

	void TextEntry::setMaxWidth(int32_t maxWidth)
	{
		if (this->maxWidth == maxWidth)
			return;
		this->maxWidth = maxWidth;
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
		recalcWidth();
		recalcHeight();
	}

	int32_t TextEntry::getWidth()
	{
		if (this->mustCalcWidth)
		{
			if (!getFont())
				this->width = 0;
			else
				this->width = getFont()->getWidth(this->text);
			if (this->maxWidth > 0 && this->width > this->maxWidth)
				this->width = this->maxWidth;
			this->mustCalcWidth = false;
		}
		return (this->width * this->scale.x);
	}

	int32_t TextEntry::getHeight()
	{
		if (this->mustCalcHeight)
		{
			this->height = 0;
			if (getFont())
			{
				this->height = getLineHeight();
				char *iter = const_cast<char*>(this->text.c_str());
				char *end = iter + this->text.length();
				float x = 0;
				for (uint32_t i = 0; i < this->charsNumber; ++i)
				{
					uint32_t character = utf8::next(iter, end);
					if (character == '\n')
					{
						x = 0;
						this->height += getLineHeight();
						continue;
					}
					FontGlyph *glyph = getFont()->getGlyph(character);
					if (!glyph)
						continue;
					x += glyph->getAdvance();
					if (this->maxWidth > 0 && x >= this->maxWidth)
					{
						this->height += getLineHeight();
						x = 0;
					}
				}
			}
			this->mustCalcHeight = false;
		}
		return (this->height * this->scale.y);
	}

	int32_t TextEntry::getLineHeight()
	{
		if (this->lineHeight == -1)
		{
			if (!getFont())
				return (0);
			return (getFont()->getLineHeight() * this->scale.y);
		}
		return (this->lineHeight * this->scale.y);
	}

}
