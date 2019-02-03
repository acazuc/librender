#include "TextBase.h"
#include "./DrawableBuffers.h"
#include <libunicode/utf8.h>

namespace librender
{

	TextBase::TextBase()
	: shadowColor(Color::BLACK)
	, color(Color::WHITE)
	, fontRevision(0)
	, charsNumber(0)
	, shadowSize(0)
	, lineHeight(-1)
	, maxWidth(-1)
	, shadowX(0)
	, shadowY(0)
	, height(0)
	, width(0)
	, mustCalcHeight(false)
	, mustCalcWidth(false)
	{
	}

	void TextBase::fillIndices(std::vector<uint32_t>::iterator indices)
	{
		std::copy(this->indices.begin(), this->indices.end(), indices);
	}

	void TextBase::fillTexCoords(std::vector<Vec2>::iterator texCoords)
	{
		std::copy(this->texCoords.begin(), this->texCoords.end(), texCoords);
	}

	void TextBase::fillVertexes(std::vector<Vec2>::iterator vertexes)
	{
		std::copy(this->vertexes.begin(), this->vertexes.end(), vertexes);
	}

	void TextBase::fillColors(std::vector<Vec4>::iterator colors)
	{
		std::copy(this->colors.begin(), this->colors.end(), colors);
	}

	uint32_t TextBase::getShadowLen()
	{
		if (this->shadowSize <= 0)
			return 0;
		if (this->shadowSize == 1)
			return 1;
		int32_t tmp = this->shadowSize - 1;
		int32_t tmp2 = 1 + tmp * 2;
		return tmp2 * tmp2 - 1 - 4 * tmp;
	}

	void TextBase::updateTexCoords()
	{
		char *iter = const_cast<char*>(this->text.c_str());
		char *end = iter + this->text.length();
		for (uint32_t i = 0; i < this->charsNumber; ++i)
		{
			uint32_t character = utf8::next(iter, end);
			getFont()->glChar(character, &this->texCoords[i * 4].x);
		}
		uint32_t shadowLen = getShadowLen();
		uint32_t copyCount = this->charsNumber * 4;
		for (uint32_t i = 1; i <= shadowLen; ++i)
			std::copy(this->texCoords.begin(), this->texCoords.begin() + copyCount, this->texCoords.begin() + copyCount * i);
	}

	void TextBase::updateVertexes()
	{
		uint32_t shadowLen = getShadowLen();
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
				std::fill(this->vertexes.begin() + index, this->vertexes.begin() + index + 4, 0);
				index += 4;
				continue;
			}
			Glyph *glyph = getFont()->getGlyph(character);
			if (!glyph)
			{
				std::fill(this->vertexes.begin() + index, this->vertexes.begin() + index + 4, 0);
				index += 4;
				continue;
			}
			else
			{
				float charWidth = glyph->getAdvance();
				if (this->maxWidth > 0 && x && x + charWidth >= this->maxWidth)
				{
					y += getLineHeight();
					x = 0;
				}
				float charRenderLeft = x + glyph->getOffsetX();
				float charRenderTop = y + glyph->getOffsetY();
				float charRenderRight = charRenderLeft + glyph->getWidth();
				float charRenderBottom = charRenderTop + glyph->getHeight();
				vertexes[index].x = charRenderLeft;
				vertexes[index].y = charRenderTop;
				++index;
				vertexes[index].x = charRenderRight;
				vertexes[index].y = charRenderTop;
				++index;
				vertexes[index].x = charRenderRight;
				vertexes[index].y = charRenderBottom;
				++index;
				vertexes[index].x = charRenderLeft;
				vertexes[index].y = charRenderBottom;
				++index;
				x += charWidth;
			}
		}
		if (!shadowLen)
			return;
		uint32_t tmp = 1 + (this->shadowSize - 1) * 2;
		uint8_t arrCount = 0;
		uint32_t tmp2 = shadowLen * this->charsNumber * 4;
		uint32_t tmptmp = tmp * tmp;
		for (uint32_t i = 0; i < tmptmp; ++i)
		{
			int32_t sx = i % tmp - (this->shadowSize - 1);
			int32_t sy = i / tmp - (this->shadowSize - 1);
			if (std::abs(sx) == std::abs(sy) && this->shadowSize != 1)
				continue;
			uint32_t index = this->charsNumber * 4 * arrCount;
			Vec2 vtmp(this->shadowX + sx, this->shadowY + sy);
			for (uint32_t j = 0; j < this->charsNumber * 4; ++j)
				this->vertexes[index + j] = this->vertexes[tmp2 + j] + vtmp;
			arrCount++;
		}
	}

	void TextBase::updateIndices()
	{
		size_t count = 0;
		uint32_t currentIndice = 0;
		for (size_t i = 0; i < this->indicesNumber / 6; ++i)
		{
			indices[count++] = currentIndice + 0;
			indices[count++] = currentIndice + 3;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 3;
			indices[count++] = currentIndice + 2;
			currentIndice += 4;
		}
	}

	void TextBase::updateColors()
	{
		uint32_t copyCount = this->charsNumber * 4;
		uint32_t shadowLen = getShadowLen();
		{
			uint32_t tmp = shadowLen * copyCount;
			std::fill(this->colors.begin() + tmp, this->colors.begin() + tmp + copyCount, this->color);
		}
		if (!shadowLen)
			return;
		std::fill(this->colors.begin(), this->colors.begin() + copyCount, this->shadowColor);
		for (uint32_t i = 1; i < shadowLen; ++i)
			std::copy(this->colors.begin(), this->colors.begin() + copyCount, this->colors.begin() + copyCount * i);
	}

	void TextBase::updateBuffers()
	{
		Font *font = getFont();
		if (!font)
			return;
		if (this->updatesRequired & (DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES))
		{
			//Hack fix, load all glyphs before update
			char *iter = const_cast<char*>(this->text.c_str());
			char *end = iter + this->text.length();
			for (uint32_t i = 0; i < this->charsNumber; ++i)
			{
				uint32_t character = utf8::next(iter, end);
				font->getGlyph(character);
			}
		}
		font->glUpdate();
		if (font->getRevision() != this->fontRevision)
		{
			this->fontRevision = font->getRevision();
			requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
		}
		DrawableBase::updateBuffers();
	}

	void TextBase::setText(std::string &text)
	{
		recalcWidth();
		recalcHeight();
		this->text = text;
		uint32_t newLen = utf8::distance(this->text.begin(), this->text.end());
		if (this->charsNumber != newLen)
		{
			this->charsNumber = newLen;
			uint32_t shadowLen = getShadowLen();
			setVerticesNumber(this->charsNumber * 4 * (1 + shadowLen));
			setIndicesNumber(this->charsNumber * 6 * (1 + shadowLen));
			this->texCoords.resize(getVerticesNumber());
			this->vertexes.resize(getVerticesNumber());
			this->colors.resize(getVerticesNumber());
			this->indices.resize(getIndicesNumber());
			requireUpdates(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_COLORS);
		}
		else
		{
			requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS);
		}
	}

	void TextBase::setShadowColor(Color color)
	{
		if (color == this->shadowColor)
			return;
		this->shadowColor = color;
		requireUpdates(DRAWABLE_BUFFER_COLORS);
	}

	void TextBase::setColor(Color color)
	{
		if (color == this->color)
			return;
		this->color = color;
		requireUpdates(DRAWABLE_BUFFER_COLORS);
	}

	void TextBase::setShadowSize(int16_t shadowSize)
	{
		if (this->shadowSize == shadowSize)
			return;
		this->shadowSize = shadowSize;
		uint32_t shadowLen = getShadowLen();
		setVerticesNumber(this->charsNumber * 4 * (1 + shadowLen));
		setIndicesNumber(this->charsNumber * 6 * (1 + shadowLen));
		this->texCoords.resize(getVerticesNumber());
		this->vertexes.resize(getVerticesNumber());
		this->colors.resize(getVerticesNumber());
		this->indices.resize(getIndicesNumber());
		requireUpdates(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_COLORS);
	}

	void TextBase::setShadowX(int32_t shadowX)
	{
		if (this->shadowX == shadowX)
			return;
		this->shadowX = shadowX;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES);
	}

	void TextBase::setShadowY(int32_t shadowY)
	{
		if (this->shadowY == shadowY)
			return;
		this->shadowY = shadowY;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES);
	}

	void TextBase::setMaxWidth(int32_t maxWidth)
	{
		if (this->maxWidth == maxWidth)
			return;
		this->maxWidth = maxWidth;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES);
		recalcWidth();
		recalcHeight();
	}

	int32_t TextBase::getWidth()
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
		return this->width * this->scale.x;
	}

	int32_t TextBase::getHeight()
	{
		if (!this->mustCalcHeight)
			return this->height * this->scale.y;
		this->mustCalcHeight = false;
		this->height = 0;
		if (!getFont())
			return this->height * this->scale.y;
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
			Glyph *glyph = getFont()->getGlyph(character);
			if (!glyph)
				continue;
			x += glyph->getAdvance();
			if (this->maxWidth > 0 && x >= this->maxWidth)
			{
				this->height += getLineHeight();
				x = 0;
			}
		}
		return this->height * this->scale.y;
	}

	int32_t TextBase::getLineHeight()
	{
		if (this->lineHeight == -1)
		{
			if (!getFont())
				return 0;
			return getFont()->getLineHeight() * this->scale.y;
		}
		return this->lineHeight * this->scale.y;
	}

}
