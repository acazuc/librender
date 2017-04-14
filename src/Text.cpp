#include "Text.h"
#include <cstring>
#include <utf8.h>
#include <iostream>

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

namespace librender
{

	Text::Text()
	: texCoords(NULL)
	, vertex(NULL)
	, colors(NULL)
	, shadowColor(Color::WHITE)
	, color(Color::WHITE)
	, verticesNumber(0)
	, charsNumber(0)
	, updatesRequired(0)
	, shadowSize(0)
	, shadowX(0)
	, shadowY(0)
	, opacity(1)
	, scaleX(1)
	, scaleY(1)
	, x(x)
	, y(y)
	{
		//
	}

	Text::~Text()
	{
		if (this->vertex)
			delete[] (this->vertex);
		if (this->texCoords)
			delete[] (this->texCoords);
		if (this->colors)
			delete[] (this->colors);
	}

	void Text::updateVertex()
	{
		if (!this->font)
			return;
		int32_t shadowLen = (1 + this->shadowSize * 2) * (1 + this->shadowSize * 2) - 1 - this->shadowSize * 4;
		if (shadowLen < 0)
			shadowLen = 0;
		int32_t lineHeight = this->font->getLineHeight();
		int32_t x = this->x;
		int32_t y = this->y;
		char *iter = const_cast<char*>(this->text.c_str());
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t currentChar = utf8::next(iter, const_cast<char*>(this->text.c_str()) + this->text.length());
			if (currentChar == '\n')
			{
				y += lineHeight * this->scaleY;
				x = this->x;
			}
			else
			{
				int32_t charWidth = static_cast<int32_t>(this->font->getWidth(currentChar)) * this->scaleX;
				int32_t charRenderWidth = this->font->getCharRenderWidth(currentChar) * this->scaleX;
				int32_t charRenderHeight = this->font->getCharRenderHeight(currentChar) * this->scaleY;
				int32_t charRenderX = x + this->font->getCharRenderOffsetX(currentChar);
				int32_t charRenderY = y + this->font->getCharRenderOffsetY(currentChar);
				int32_t tmp = (shadowLen * this->charsNumber + i) * 8;
				this->vertex[tmp + 0] = charRenderX;
				this->vertex[tmp + 1] = charRenderY;
				this->vertex[tmp + 2] = charRenderX + charRenderWidth;
				this->vertex[tmp + 3] = charRenderY;
				this->vertex[tmp + 4] = charRenderX + charRenderWidth;
				this->vertex[tmp + 5] = charRenderY + charRenderHeight;
				this->vertex[tmp + 6] = charRenderX;
				this->vertex[tmp + 7] = charRenderY + charRenderHeight;
				x += charWidth * this->scaleX;
			}
		}
		if (this->shadowSize == 0)
			return;
		uint32_t tmp = 1 + this->shadowSize * 2;
		uint8_t arrCount = 0;
		int32_t tmp2 = shadowLen * this->charsNumber * 8;
		for (uint8_t i = 0; i < tmp * tmp; ++i)
		{
			int8_t sx = i % tmp - this->shadowSize;
			int8_t sy = i / tmp - this->shadowSize;
			if (std::abs(sx) == std::abs(sy))
				continue;
			uint32_t index = this->charsNumber * 8 * arrCount;
			uint32_t add = 0;
			for (uint32_t j = 0; j < this->charsNumber * 4; ++j)
			{
				this->vertex[index + add] = this->vertex[tmp2 + add] + (sx + this->shadowX) * this->scaleX;
				++add;
				this->vertex[index + add] = this->vertex[tmp2 + add] + (sy + this->shadowY) * this->scaleY;
				++add;
			}
			arrCount++;
		}
	}

	void Text::updateTexCoords()
	{
		if (!this->font)
			return;
		char *iter = const_cast<char*>(this->text.c_str());
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t currentChar = utf8::next(iter, const_cast<char*>(this->text.c_str()) + this->text.length());
			this->font->glArrayCharPart(currentChar, &this->texCoords[i * 8]);
		}
		if (this->shadowSize == 0)
			return;
		uint32_t max = (1 + this->shadowSize * 2) * (1 + this->shadowSize * 2) - 1 - 4 * this->shadowSize;
		for (uint32_t i = 0; i < max; ++i)
		{
			std::memcpy(&this->texCoords[this->charsNumber * 8 * (i + 1)], &this->texCoords[0], this->charsNumber * 8 * sizeof(*this->texCoords));
		}
	}

	void Text::updateColors()
	{
		int32_t shadowLen = (1 + this->shadowSize * 2) * (1 + this->shadowSize * 2) - 1 - this->shadowSize * 4;
		if (shadowLen < 0)
			shadowLen = 0;
		{
			float tab[4] = {this->color.getRed(), this->color.getGreen(), this->color.getBlue(), this->color.getAlpha() * this->opacity};
			int32_t tmp = (shadowLen * this->charsNumber * 4) * 4;
			for (uint32_t i = 0; i < this->charsNumber * 4; ++i)
			{
				std::memcpy(&this->colors[tmp], tab, sizeof(tab));
				tmp += 4;
			}
		}
		if (this->shadowSize <= 0)
			return;
		{
			float tab[4] = {this->shadowColor.getRed(), this->shadowColor.getGreen(), this->shadowColor.getBlue(), this->shadowColor.getAlpha() * this->opacity};
			for (uint32_t i = 0; i < this->charsNumber * 4; ++i)
			{
				std::memcpy(&this->colors[i * 4], tab, sizeof(tab));
			}
		}
		uint16_t max = (1 + this->shadowSize * 2) * (1 + this->shadowSize * 2) - 1 - 4 * this->shadowSize;
		for (uint16_t i = 1; i < max; ++i)
		{
			std::memcpy(&this->colors[this->charsNumber * 4 * 4 * i], &this->colors[0], this->charsNumber * 4 * 4 * sizeof(*this->colors));
		}
	}

	void Text::resize(uint32_t len)
	{
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
		this->charsNumber = len;
		this->verticesNumber = this->charsNumber * 4;
		if (this->shadowSize > 0)
		{
			uint16_t fac = 1 + (1 + this->shadowSize * 2) * (1 + this->shadowSize * 2);
			fac -= 1 + 4 * this->shadowSize;
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

	void Text::draw()
	{
		if (!this->font)
			return;
		if (this->updatesRequired & UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & UPDATE_VERTEX)
			updateVertex();
		if (this->updatesRequired & UPDATE_COLORS)
			updateColors();
		this->updatesRequired = 0;
		this->font->bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors);
		glVertexPointer(2, GL_FLOAT, 0, this->vertex);
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords);
		glDrawArrays(GL_QUADS, 0, this->verticesNumber);
	}

	void Text::setText(std::string &text)
	{
		uint32_t newLen = utf8::distance(text.begin(), text.end());
		if (this->charsNumber != newLen)
			resize(newLen);
		this->text = text;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void Text::setShadowColor(Color &color)
	{
		if (!color.compare(this->shadowColor))
			return;
		this->shadowColor = color;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void Text::setColor(Color &color)
	{
		if (!color.compare(this->color))
			return;
		this->color = color;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void Text::setFont(Font *font)
	{
		if (font == this->font)
			return;
		this->font = font;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void Text::setShadowSize(int16_t shadowSize)
	{
		if (this->shadowSize == shadowSize)
			return;
		this->shadowSize = shadowSize;
		resize(this->charsNumber);
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void Text::setShadowX(int16_t shadowX)
	{
		if (this->shadowX == shadowX)
			return;
		this->shadowX = shadowX;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void Text::setShadowY(int16_t shadowY)
	{
		if (this->shadowY == shadowY)
			return;
		this->shadowY = shadowY;
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void Text::setOpacity(float opacity)
	{
		if (this->opacity == opacity)
			return;
		this->opacity = opacity;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void Text::setScaleX(float scaleX)
	{
		if (this->scaleX == scaleX)
			return;
		this->scaleX = scaleX;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void Text::setScaleY(float scaleY)
	{
		if (this->scaleY == scaleY)
			return;
		this->scaleY = scaleY;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void Text::setScale(float scale)
	{
		setScaleX(scale);
		setScaleY(scale);
	}

	void Text::setX(float x)
	{
		moveX(x - this->x);
	}

	void Text::setY(float y)
	{
		moveY(y - this->y);
	}

	void Text::setPos(float x, float y)
	{
		movePos(x - this->x, y - this->y);
	}

	void Text::moveX(float deltaX)
	{
		if (!deltaX)
			return;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
		{
			this->vertex[i * 2 + 0] += deltaX;
		}
		this->x += deltaX;
	}

	void Text::moveY(float deltaY)
	{
		if (!deltaY)
			return;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
		{
			this->vertex[i * 2 + 1] += deltaY;
		}
		this->y += deltaY;
	}

	void Text::movePos(float deltaX, float deltaY)
	{
		if (!deltaX && !deltaY)
			return;
		if (!deltaX)
		{
			moveY(deltaY);
			return;
		}
		if (!deltaY)
		{
			moveX(deltaX);
			return;
		}
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
		{
			this->vertex[i * 2 + 0] += deltaX;
			this->vertex[i * 2 + 1] += deltaY;
		}
		this->x += deltaX;
		this->y += deltaY;
	}

}
