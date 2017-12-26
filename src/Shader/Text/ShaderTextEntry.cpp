#include "ShaderTextEntry.h"
#include "./ShaderTextUpdate.h"
#include "../../GL.h"
#include <cstring>
#include <utf8.h>

namespace librender
{

	ShaderTextEntry::ShaderTextEntry()
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

	ShaderTextEntry::~ShaderTextEntry()
	{
		delete[] (this->texCoords);
		delete[] (this->vertexes);
		delete[] (this->colors);
	}

	void ShaderTextEntry::fillTexCoords(Vec2 *texCoords)
	{
		char *iter = const_cast<char*>(this->text.c_str());
		char *end = iter + this->text.length();
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t currentChar = utf8::next(iter, end);
			getFont()->glArrayCharPart(currentChar, reinterpret_cast<float*>(&texCoords[i * 4]));
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
		{
			std::memcpy(&texCoords[this->charsNumber * 4 * (i + 1)], &texCoords[0], this->charsNumber * 4 * sizeof(*texCoords));
		}
	}

	void ShaderTextEntry::fillVertexes(Vec2 *vertexes)
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
			uint32_t currentChar = utf8::next(iter, end);
			if (currentChar == '\n')
			{
				y += getLineHeight();
				x = 0;
				std::memset(&vertexes[index], 0, 4 * sizeof(*this->vertexes));
				index += 4;
				continue;
			}
			FontGlyph *glyph = getFont()->getGlyph(currentChar);
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
				index++;
				vertexes[index].x = charRenderX + charRenderWidth;
				vertexes[index].y = charRenderY;
				index++;
				vertexes[index].x = charRenderX + charRenderWidth;
				vertexes[index].y = charRenderY + charRenderHeight;
				index++;
				vertexes[index].x = charRenderX;
				vertexes[index].y = charRenderY + charRenderHeight;
				index++;
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
		int32_t tmptmp = tmp * tmp;
		for (uint8_t i = 0; i < tmptmp; ++i)
		{
			int8_t sx = i % tmp - (this->shadowSize - 1);
			int8_t sy = i / tmp - (this->shadowSize - 1);
			if (std::abs(sx) == std::abs(sy) && this->shadowSize != 1)
				continue;
			uint32_t index = this->charsNumber * 4 * arrCount;
			uint32_t add = 0;
			Vec2 vtmp(this->shadowX + sx, this->shadowY + sy);
			for (uint32_t j = 0; j < this->charsNumber * 4; ++j)
			{
				vertexes[index + add] = vertexes[tmp2 + add] + vtmp;
				++add;
			}
			arrCount++;
		}
	}

	void ShaderTextEntry::fillColors(Vec4 *colors)
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
				tmp++;
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
			std::memcpy(&colors[this->charsNumber * 4 * i], &colors[0], this->charsNumber * 4 * 4 * sizeof(*colors));
	}

	void ShaderTextEntry::update()
	{
		if (!getFont())
			return;
		if (this->updatesRequired & SHADER_TEXT_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & SHADER_TEXT_UPDATE_VERTEXES)
			updateVertexes();
		if (this->updatesRequired & SHADER_TEXT_UPDATE_COLORS)
			updateColors();
		this->updatesRequired = 0;
	}

	void ShaderTextEntry::resize(uint32_t len)
	{
		this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= SHADER_TEXT_UPDATE_TEX_COORDS;
		this->updatesRequired |= SHADER_TEXT_UPDATE_COLORS;
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
		this->texCoords = new Vec2[this->verticesNumber + 1];
		delete[] (this->vertexes);
		this->vertexes = new Vec2[this->verticesNumber + 1];
		delete[] (this->colors);
		this->colors = new Vec4[this->verticesNumber + 1];
	}

	void ShaderTextEntry::setText(std::string &text)
	{
		recalcWidth();
		recalcHeight();
		uint32_t newLen = utf8::distance(text.begin(), text.end());
		if (this->charsNumber != newLen)
			resize(newLen);
		this->text = text;
		this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= SHADER_TEXT_UPDATE_TEX_COORDS;
	}

	void ShaderTextEntry::setShadowColor(Color &color)
	{
		if (!color.compare(this->shadowColor))
			return;
		this->shadowColor = color;
		this->updatesRequired |= SHADER_TEXT_UPDATE_COLORS;
	}

	void ShaderTextEntry::setColor(Color &color)
	{
		if (!color.compare(this->color))
			return;
		this->color = color;
		this->updatesRequired |= SHADER_TEXT_UPDATE_COLORS;
	}

	void ShaderTextEntry::setShadowSize(int16_t shadowSize)
	{
		if (this->shadowSize == shadowSize)
			return;
		this->shadowSize = shadowSize;
		resize(this->charsNumber);
		this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= SHADER_TEXT_UPDATE_TEX_COORDS;
		this->updatesRequired |= SHADER_TEXT_UPDATE_COLORS;
	}

	void ShaderTextEntry::setShadowX(int32_t shadowX)
	{
		if (this->shadowX == shadowX)
			return;
		this->shadowX = shadowX;
		this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
	}

	void ShaderTextEntry::setShadowY(int32_t shadowY)
	{
		if (this->shadowY == shadowY)
			return;
		this->shadowY = shadowY;
		this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
	}

	void ShaderTextEntry::setOpacity(float opacity)
	{
		if (this->opacity == opacity)
			return;
		this->opacity = opacity;
		this->updatesRequired |= SHADER_TEXT_UPDATE_COLORS;
	}

	void ShaderTextEntry::setScaleX(float scaleX)
	{
		if (this->scale.x == scaleX)
			return;
		this->scale.x = scaleX;
	}

	void ShaderTextEntry::setScaleY(float scaleY)
	{
		if (this->scale.y == scaleY)
			return;
		this->scale.y = scaleY;
	}

	void ShaderTextEntry::setMaxWidth(int32_t maxWidth)
	{
		if (this->maxWidth == maxWidth)
			return;
		this->maxWidth = maxWidth;
		this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
	}

	int32_t ShaderTextEntry::getWidth()
	{
		if (this->mustCalcWidth)
		{
			if (!getFont())
				this->width = 0;
			else
				this->width = getFont()->getWidth(this->text);
			this->mustCalcWidth = false;
		}
		return (this->width * this->scale.x);
	}

	int32_t ShaderTextEntry::getHeight()
	{
		if (this->mustCalcWidth)
		{
			if (!getFont())
				this->height = 0;
			else
				this->height = getFont()->getHeight(this->text);
			this->mustCalcHeight = false;
		}
		return (this->height * this->scale.y);
	}

	int32_t ShaderTextEntry::getLineHeight()
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
