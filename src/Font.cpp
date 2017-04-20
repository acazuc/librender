#include "Font.h"
#include "utf8.h"
#include <cstdlib>
#include <cstring>
#include <cmath>

#define WIDTH_CORRECT 2

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
		glDeleteTextures(1, &this->textureID);
		for (uint32_t i = 0; i < LIBRENDER_FONT_MODEL_CHARS_NUMBER; ++i)
		{
			if (this->glyphs[i])
				delete (this->glyphs[i]);
		}
		delete[] (this->glyphs);
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
		uint32_t maxHeight = 0;
		uint32_t maxWidth = 0;
		for (uint32_t i = 0; i < LIBRENDER_FONT_MODEL_CHARS_NUMBER; ++i)
		{
			FontGlyph *glyph = this->glyphs[i];
			if (!glyph)
				continue;
			totalWidth += glyph->getWidth() + 1;
			if (glyph->getHeight() > maxHeight)
				maxHeight = glyph->getHeight();
			if (glyph->getWidth() > maxWidth)
				maxWidth = glyph->getWidth() + 1;
		}
		this->height = maxHeight;
		uint32_t size = std::sqrt(totalWidth * (maxHeight + 2)) + maxWidth + maxHeight + 4;
		char *data = new char[size * size * 4];
		std::memset(data, 0xff, size * size * 4);
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
				data[((y + tY) * size + x + tX) * 4 + 3] = glyph_data[tY * glyph->getWidth() + tX];
			}
		}
	}

	void Font::buildGLTexture(char *data, uint32_t width, uint32_t height)
	{
		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

	int32_t Font::getWidth(uint32_t character)
	{
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
			return (0);
		return (glyph->getAdvance());
	}

	uint32_t Font::getCharRenderWidth(uint32_t character)
	{
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
			return (0);
		return (glyph->getWidth());
	}

	uint32_t Font::getCharRenderHeight(uint32_t character)
	{
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
			return (0);
		return (glyph->getHeight());
	}

	uint32_t Font::getCharRenderOffsetX(uint32_t character)
	{
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
			return (0);
		return (glyph->getOffsetX());
	}

	uint32_t Font::getCharRenderOffsetY(uint32_t character)
	{
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
			return (0);
		return (glyph->getOffsetY());
	}

	int32_t Font::getWidth(std::string &text)
	{
		char *iter = const_cast<char*>(text.c_str());
		uint32_t maxWidth = 0;
		uint32_t currentWidth = 0;
		char *end = const_cast<char*>(text.c_str()) + text.length();
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
				currentWidth += getWidth(currentChar);
		}
		if (currentWidth > maxWidth)
			maxWidth = currentWidth;
		return (maxWidth);
	}

	int32_t Font::getHeight(std::string &text)
	{
		char *iter = const_cast<char*>(text.c_str());
		uint32_t nlNb = 1;
		char *end = const_cast<char*>(text.c_str() + text.length());
		while (iter != end)
		{
			if (utf8::next(iter, end) == '\n')
				nlNb++;
		}
		return (this->height * nlNb);
	}

	void Font::drawBegin()
	{
		bind();
		glBegin(GL_QUADS);
	}

	void Font::drawEnd()
	{
		glEnd();
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

	void Font::drawChar(float x, float y, uint32_t character, Color &color, float scaleX, float scaleY, float opacity)
	{
		if (!opacity)
			return;
		bind();
		glBegin(GL_QUADS);
		glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() * opacity);
		drawCharPart(x, y, character, scaleX, scaleY);
		glEnd();
	}

	void Font::drawCharPart(float x, float y, uint32_t character, float scaleX, float scaleY)
	{
		if (character == '\n')
			return;
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
			return;
		drawQuad(x + glyph->getOffsetX() * scaleX, y + glyph->getOffsetY() * scaleY
			, glyph->getWidth() * scaleX, glyph->getHeight() * scaleY
			, glyph->getTexX(), glyph->getTexY()
			, glyph->getWidth(), glyph->getHeight());
	}

	void Font::glArrayCharPart(uint32_t character, float *texCoords)
	{
		if (character == '\n')
			return;
		FontGlyph *glyph = getGlyph(character);
		if (!glyph)
		{
			std::memset(texCoords, 0, 8 * sizeof(*texCoords));
			return;
		}
		glArrayQuad(glyph->getTexX(), glyph->getTexY(), glyph->getWidth(), glyph->getHeight(), texCoords);
	}

	void Font::drawStringPart(float x, float y, std::string &text, Color &color, float opacity)
	{
		drawStringPart(x, y, text, color, 1, 1, opacity);
	}

	void Font::drawStringPart(float x, float y, std::string &text, Color &color, float scaleX, float scaleY, float opacity)
	{
		if (!opacity)
			return;
		float totalHeight = 0;
		float totalWidth = 0;
		char *iter = const_cast<char*>(text.c_str());
		char *end = const_cast<char*>(text.c_str() + text.length());
		glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() * opacity);
		while (iter != end)
		{
			uint32_t currentChar = utf8::next(iter, end);
			if (currentChar == '\n')
			{
				totalHeight += this->height * scaleY;
				totalWidth = 0;
			}
			else if (currentChar < LIBRENDER_FONT_MODEL_CHARS_NUMBER && this->glyphs[currentChar])
			{
				drawCharPart(totalWidth + x, totalHeight + y, currentChar, scaleX, scaleY);
				totalWidth += getWidth(currentChar) * scaleX;
			}
		}
	}

	void Font::drawString(float x, float y, std::string &text, Color &color, float opacity)
	{
		drawString(x, y, text, color, 1, 1, opacity);
	}

	void Font::drawString(float x, float y, std::string &text, Color &color, float scaleX, float scaleY, float opacity)
	{
		if (!opacity)
			return;
		bind();
		glBegin(GL_QUADS);
		drawStringPart(x, y, text, color, scaleX, scaleY, opacity);
		glEnd();
	}

	void Font::drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float opacity)
	{
		drawStringShadow(x, y, text, color, shadowColor, shadowSize, 0, 0, 1, 1, opacity);
	}

	void Font::drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float scaleX, float scaleY, float opacity)
	{
		drawStringShadow(x, y, text, color, shadowColor, shadowSize, 0, 0, scaleX, scaleY, opacity);
	}

	void Font::drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY)
	{
		drawStringShadow(x, y, text, color, shadowColor, shadowSize, shadowX, shadowY, 1, 1, 1);
	}

	void Font::drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY, float scaleX, float scaleY, float opacity)
	{
		if (!opacity)
			return;
		bind();
		glBegin(GL_QUADS);
		drawStringShadowPart(x, y, text, color, shadowColor, shadowSize, shadowX, shadowY, scaleX, scaleY, opacity);
		glEnd();
	}

	void Font::drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float opacity)
	{
		drawStringShadowPart(x, y, text, color, shadowColor, shadowSize, 0, 0, 1, 1, opacity);
	}

	void Font::drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float scaleX, float scaleY, float opacity)
	{
		drawStringShadowPart(x, y, text, color, shadowColor, shadowSize, 0, 0, scaleX, scaleY, opacity);
	}

	void Font::drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY)
	{
		drawStringShadowPart(x, y, text, color, shadowColor, shadowSize, shadowX, shadowY, 1, 1, 1);
	}

	void Font::drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY, float scaleX, float scaleY, float opacity)
	{
		if (!opacity)
			return;
		for (float xx = x - shadowSize * scaleX + shadowX;xx <= x + shadowSize * scaleX + shadowX;xx += scaleX)
		{
			for (float yy = y - shadowSize * scaleY + shadowY;yy <= y + shadowSize * scaleY + shadowY;yy += scaleY)
			{
				if (std::fabs(xx - x - shadowX) != std::fabs(yy - y - shadowY))
				{
					drawStringPart(xx, yy, text, shadowColor, scaleX, scaleY, opacity);
				}
			}
		}
		drawStringPart(x, y, text, color, scaleX, scaleY, opacity);
	}

}
