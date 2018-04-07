#include "Font.h"
#include "../GL.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <utf8.h>
#include <cmath>

#define CLUSTER_SIZE 256

namespace librender
{

	Font::Font(FontModel &parent, uint32_t size)
	: parent(parent)
	, textureHeight(0)
	, textureWidth(0)
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
	}

	Font::~Font()
	{
		//Empty
	}
	
	void Font::bind()
	{
		this->texture.bind();
	}

	FontGlyph *Font::loadGlyph(uint32_t character)
	{
		if (!this->parent.setSize(this->size))
			return (NULL);
		if (character < 0x1f)
			return (NULL);
		uint32_t codepoint = FT_Get_Char_Index(this->parent.getFtFace(), character);
		if (!codepoint)
			return (NULL);
		if (FT_Load_Glyph(this->parent.getFtFace(), codepoint, FT_LOAD_DEFAULT))
			return (NULL);
		if (!this->parent.getFtFace()->glyph->advance.x)
			return (NULL);
		if (FT_Render_Glyph(this->parent.getFtFace()->glyph, FT_RENDER_MODE_NORMAL))
			return (NULL);
		FontGlyph tmp(this->parent.getFtFace()->glyph->advance.x >> 6, \
				this->parent.getFtFace()->glyph->bitmap.width, this->parent.getFtFace()->glyph->bitmap.rows, \
				this->parent.getFtFace()->glyph->bitmap_left, this->size - this->parent.getFtFace()->glyph->bitmap_top);
		if (tmp.getWidth() + 2 > CLUSTER_SIZE || tmp.getHeight() + 2 > CLUSTER_SIZE)
			return (NULL);
		FontGlyph &glyph = this->glyphs.emplace(character, tmp).first->second;
		this->tmpGlyphs.resize(this->tmpGlyphs.size() + 1);
		FontTmpGlyph &tmpGlyph = this->tmpGlyphs.back();
		tmpGlyph.datas.resize(glyph.getWidth() * glyph.getHeight());
		std::memcpy(tmpGlyph.datas.data(), this->parent.getFtFace()->glyph->bitmap.buffer, glyph.getWidth() * glyph.getHeight());
		tmpGlyph.character = character;
		return (&glyph);
	}

	void Font::charCopy(char *data, uint32_t x, uint32_t y, uint32_t width, FontGlyph &glyph, char *glyphData)
	{
		for (uint32_t tY = 0; tY < glyph.getHeight(); ++tY)
			std::memcpy(&data[(y + tY) * width + x], &glyphData[tY * glyph.getWidth()], glyph.getWidth());
	}

	bool Font::findPlace(uint32_t width, uint32_t height, uint32_t *x, uint32_t *y)
	{
		for (uint32_t i = 0; i < this->clusters.size(); ++i)
		{
			if (this->clusters[i].findPlace(width, height, x, y))
				return (true);
		}
	}

	bool FontCluster::findPlace(uint32_t width, uint32_t height, uint32_t *x, uint32_t *y)
	{
		if (width > this->width || height > this->height)
			return (false);
		for (uint32_t i = 0; i < this->lines.size(); ++i)
		{
			FontClusterLine &line = this->lines[i];
			if (line.height >= height)
			{
				if (this->width - line.width >= width)
				{
					*x = this->x + line.width;
					*y = this->y + line.y;
					line.width += width;
					if (height > line.height)
						line.height = height;
					return (true);
				}
				continue;
			}
			if (i != this->lines.size() - 1)
				continue;
			if (this->height - line.y < height)
				continue;
			line.height = height;
			*x = this->x + line.width;
			*y = this->y + line.y;
			line.width += width;
			if (height > line.height)
				line.height = height;
			return (true);
		}
		uint32_t newY = this->lines.size() ? this->lines.back().y + this->lines.back().height : 0;
		if (height > this->height - newY)
			return (false);
		this->lines.resize(this->lines.size() + 1);
		this->lines.back().y = newY;
		this->lines.back().width = width;
		this->lines.back().height = height;
		*x = this->x;
		*y = this->y + newY;
		return (true);
	}

	FontGlyph *Font::getGlyph(uint32_t character)
	{
		std::unordered_map<uint32_t, FontGlyph>::iterator iter = this->glyphs.find(character);
		if (iter != this->glyphs.end())
			return (&iter->second);
		FontGlyph *glyph = loadGlyph(character);
		if (glyph)
			return (glyph);
		if (character != '?')
			return (getGlyph('?'));
		FontGlyph tmp(0, 0, 0, 0, 0);
		tmp.setTexX(0);
		tmp.setTexY(0);
		this->glyphs.emplace(character, tmp);
		return (NULL);
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

	void Font::glUpdate()
	{
		if (!this->tmpGlyphs.size())
			return;
		bool needUpdate = false;
		std::vector<char> textureDatas(this->textureWidth * this->textureHeight * 4);
		this->texture.bind();
		glGetTexImage(GL_TEXTURE_2D, 0, GL_ALPHA, GL_UNSIGNED_BYTE, textureDatas.data());
		for (uint32_t i = 0; i < this->tmpGlyphs.size(); ++i)
		{
			FontTmpGlyph &tmpGlyph = this->tmpGlyphs[i];
			std::unordered_map<uint32_t, FontGlyph>::iterator iter = this->glyphs.find(tmpGlyph.character);
			if (iter == this->glyphs.end())
				continue;
			FontGlyph &glyph = iter->second;
			uint32_t x;
			uint32_t y;
			if (findPlace(glyph.getWidth() + 2, glyph.getHeight() + 2, &x, &y))
			{
				glyph.setTexX(x + 1);
				glyph.setTexY(y + 1);
				charCopy(textureDatas.data(), x + 1, y + 1, this->textureWidth, glyph, tmpGlyph.datas.data());
				needUpdate = true;
				continue;
			}
			this->clusters.resize(this->clusters.size() + 1);
			FontCluster &cluster = this->clusters.back();
			cluster.width = CLUSTER_SIZE;
			cluster.height = CLUSTER_SIZE;
			cluster.x = 0;
			cluster.y = this->textureHeight;
			if (!cluster.findPlace(glyph.getWidth() + 2, glyph.getHeight() + 2, &x, &y))
			{
				glyph.setWidth(0);
				glyph.setHeight(0);
				glyph.setTexX(0);
				glyph.setTexY(0);
				continue;
			}
			glyph.setTexX(x + 1);
			glyph.setTexY(y + 1);
			if (this->textureWidth == 0)
				this->textureWidth = CLUSTER_SIZE;
			this->textureHeight += CLUSTER_SIZE;
			textureDatas.resize(this->textureWidth * this->textureHeight, 0);
			charCopy(textureDatas.data(), x + 1, y + 1, this->textureWidth, glyph, tmpGlyph.datas.data());
			needUpdate = true;
		}
		this->tmpGlyphs.clear();
		if (needUpdate)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, this->textureWidth, this->textureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, textureDatas.data());
			++this->revision;
		}
	}

	void Font::glArrayQuad(int32_t texX, int32_t texY, int32_t texWidth, int32_t texHeight, float *texCoords)
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
