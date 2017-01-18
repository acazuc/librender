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
		this->glyphs = new FontGlyph*[UTILS_FONT_CHARS_NUMBER];
		this->glyphs_datas = new char*[UTILS_FONT_CHARS_NUMBER];
		loadList(size);
		createSet();
		delete[] (this->glyphs_datas);
	}

	Font::~Font()
	{
		glDeleteTextures(1, &this->textureID);
		for (uint32_t i = 0; i < UTILS_FONT_CHARS_NUMBER; ++i)
		{
			if (this->glyphs[i])
				delete (this->glyphs[i]);
		}
		delete[] (this->glyphs);
	}

	void Font::loadList(int size)
	{
		for (uint32_t i = 0; i < UTILS_FONT_CHARS_NUMBER; ++i)
		{
			this->glyphs[i] = NULL;
			if (!this->parent->isAvailable(i))
				continue;
			if (FT_Load_Char(this->ftFace, i, FT_LOAD_RENDER))
				continue;
			this->glyphs[i] = new FontGlyph();
			this->glyphs[i]->width = this->ftFace->glyph->bitmap.width;
			this->glyphs[i]->height = this->ftFace->glyph->bitmap.rows;
			this->glyphs[i]->advance = this->ftFace->glyph->advance.x >> 6;
			this->glyphs[i]->offsetY = size - this->ftFace->glyph->bitmap_top;
			this->glyphs[i]->offsetX = this->ftFace->glyph->bitmap_left;
			this->glyphs_datas[i] = new char[this->glyphs[i]->width * this->glyphs[i]->height];
			std::memcpy(this->glyphs_datas[i], this->ftFace->glyph->bitmap.buffer, this->glyphs[i]->width * this->glyphs[i]->height);
		}
	}

	void Font::createSet()
	{
		char *data;
		uint32_t totalWidth;
		uint32_t lineHeight;
		uint32_t maxHeight;
		uint32_t maxWidth;
		uint32_t size;
		uint32_t x;
		uint32_t y;

		totalWidth = 0;
		maxHeight = 0;
		maxWidth = 0;
		for (uint32_t i = 0; i < UTILS_FONT_CHARS_NUMBER; ++i)
		{
			if (!this->glyphs[i])
				continue;
			totalWidth += this->glyphs[i]->width + 1;
			if (this->glyphs[i]->height > maxHeight)
				maxHeight = this->glyphs[i]->height;
			if (this->glyphs[i]->width > maxWidth)
				maxWidth = this->glyphs[i]->width + 1;
		}
		this->height = maxHeight;
		size = std::sqrt(totalWidth * (maxHeight + 2)) + maxWidth + (maxHeight + 2);
		data = new char[size * size * 4];
		std::memset(data, 0, size * size * 4);
		x = 1;
		y = 1;
		lineHeight = 0;
		for (uint32_t i = 0; i < UTILS_FONT_CHARS_NUMBER; ++i)
		{
			if (!this->glyphs[i])
				continue;
			if (x + this->glyphs[i]->width + 2 >= size)
			{
				x = 1;
				y += lineHeight + 1;
				lineHeight = 0;
			}
			this->glyphs[i]->x = x;
			this->glyphs[i]->y = y;
			if (this->glyphs[i]->height > lineHeight)
				lineHeight = this->glyphs[i]->height;
			copyChar(x, y, data, size, this->glyphs[i], this->glyphs_datas[i]);
			delete[] (this->glyphs_datas[i]);
			x += this->glyphs[i]->width + 1;
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

	void Font::copyChar(int32_t x, int32_t y, char *data, uint32_t size, t_utils_font_glyph *glyph, char *glyph_data)
	{
		for (uint32_t tY = 0; tY < glyph->height; ++tY)
		{
			for (uint32_t tX = 0; tX < glyph->width; ++tX)
			{
				reinterpret_cast<int*>(data)[((y + tY) * size + x + tX)] = 0xffffffff;
				data[((y + tY) * size + x + tX) * 4 + 3] = glyph_data[tY * glyph->width + tX];
			}
		}
	}

	void Font::buildGLTexture(char *data, uint32_t width, uint32_t height)
	{
		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	unsigned int Font::getWidth(uint32_t c)
	{
		if (c >= UTILS_FONT_CHARS_NUMBER || !this->glyphs[c])
			return (0);
		return (this->glyphs[c]->advance);
	}

	unsigned int Font::getCharRenderWidth(uint32_t c)
	{
		if (c >= UTILS_FONT_CHARS_NUMBER || !this->glyphs[c])
			return (0);
		return (this->glyphs[c]->width);
	}

	unsigned int Font::getCharRenderHeight(uint32_t c)
	{
		if (c >= UTILS_FONT_CHARS_NUMBER || !this->glyphs[c])
			return (0);
		return (this->glyphs[c]->height);
	}

	unsigned int Font::getCharRenderOffsetX(uint32_t c)
	{
		if (c >= UTILS_FONT_CHARS_NUMBER || !this->glyphs[c])
			return (0);
		return (this->glyphs[c]->offsetX);
	}

	unsigned int Font::getCharRenderOffsetY(uint32_t c)
	{
		if (c >= UTILS_FONT_CHARS_NUMBER || !this->glyphs[c])
			return (0);
		return (this->glyphs[c]->offsetY);
	}

	unsigned int Font::getWidth(std::string &text)
	{
		unsigned int currentWidth;
		unsigned int maxWidth;
		char *iter;
		uint32_t currentChar;

		iter = const_cast<char*>(text.c_str());
		maxWidth = 0;
		currentWidth = 0;
		while (iter != const_cast<char*>(text.c_str()) + text.length())
		{
			currentChar = utf8::next(iter, const_cast<char*>(text.c_str()) + text.length());
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

	unsigned int Font::getHeight(std::string &text)
	{
		unsigned int nlNb;
		char *iter;

		iter = (char*)text.c_str();
		nlNb = 1;
		while (*iter)
		{
			if (utf8::next(iter, (char*)text.c_str() + text.length()) == '\n')
				nlNb++;
		}
		return (this->height * nlNb);
	}

	void Font::drawQuad(float x, float y, float width, float height, int texX, int texY, int texWidth, int texHeight)
	{
		float textureSrcX = (float)texX / this->textureWidth;
		float textureSrcY = (float)texY / this->textureHeight;
		float renderWidth = (float)texWidth / this->textureWidth;
		float renderHeight = (float)texHeight / this->textureHeight;
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
		float textureSrcX = (float)texX / this->textureWidth;
		float textureSrcY = (float)texY / this->textureHeight;
		float renderWidth = (float)texWidth / this->textureWidth;
		float renderHeight = (float)texHeight / this->textureHeight;
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
		if (character < UTILS_FONT_CHARS_NUMBER && character != '\n' && this->glyphs[character])
		{
			drawQuad(x + this->glyphs[character]->offsetX * scaleX, y + this->glyphs[character]->offsetY * scaleY
				, this->glyphs[character]->width * scaleX, this->glyphs[character]->height * scaleY
				, this->glyphs[character]->x, this->glyphs[character]->y
				, this->glyphs[character]->width, this->glyphs[character]->height);
		}
	}

	void Font::glArrayCharPart(uint32_t character, float *texCoords)
	{
		if (character < UTILS_FONT_CHARS_NUMBER && character != '\n' && this->glyphs[character])
		{
			glArrayQuad(this->glyphs[character]->x, this->glyphs[character]->y, this->glyphs[character]->width, this->glyphs[character]->height, texCoords);
		}
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
		uint32_t currentChar;
		char *iter;

		iter = (char*)text.c_str();
		while (*iter)
		{
			glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() * opacity);
			currentChar = utf8::next(iter, (char*)text.c_str() + text.length());
			if (currentChar == '\n')
			{
				totalHeight += this->height * scaleY;
				totalWidth = 0;
			}
			else if (currentChar < UTILS_FONT_CHARS_NUMBER && this->glyphs[currentChar])
			{
				drawCharPart(totalWidth + x, totalHeight + y, currentChar, scaleX, scaleY);
				totalWidth += this->glyphs[currentChar]->advance * scaleX;
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
				if (fabs(xx - x - shadowX) != fabs(yy - y - shadowY))
				{
					drawStringPart(xx, yy, text, shadowColor, scaleX, scaleY, opacity);
				}
			}
		}
		drawStringPart(x, y, text, color, scaleX, scaleY, opacity);
	}

}
