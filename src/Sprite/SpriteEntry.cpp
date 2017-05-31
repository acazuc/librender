#include "SpriteEntry.h"
#include <cstring>

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

namespace librender
{

	SpriteEntry::SpriteEntry()
	: verticesNumber(0)
	, updatesRequired(0)
	, opacity(1)
	, scaleX(1)
	, scaleY(1)
	, x(0)
	, y(0)
	{
		texCoords[0] = 0;
		texCoords[1] = 0;
		texCoords[2] = 1;
		texCoords[3] = 0;
		texCoords[4] = 1;
		texCoords[5] = 1;
		texCoords[6] = 0;
		texCoords[7] = 1;
		for (uint8_t i = 0; i < 16; ++i)
			colors[i] = 1;
		for (uint8_t i = 0; i < 8; ++i)
			vertex[i] = 0;
	}

	SpriteEntry::~SpriteEntry()
	{
		//Empty
	}

	void SpriteEntry::fillTexCoords(GLfloat *texCoords)
	{
		std::memcpy(texCoords, this->texCoords, sizeof(this->texCoords));
	}

	void SpriteEntry::fillVertex(GLfloat *vertex)
	{
		std::memcpy(vertex, this->vertex, sizeof(this->vertex));
	}

	void SpriteEntry::fillColors(GLfloat *colors)
	{
		std::memcpy(colors, this->colors, sizeof(this->colors));
	}

	void SpriteEntry::update()
	{
		this->updatesRequired = 0;
	}

	void SpriteEntry::setColor(Color &color)
	{
		setTopLeftColor(color);
		setTopRightColor(color);
		setBotLeftColor(color);
		setBotRightColor(color);
		this->updatesRequired |= UPDATE_COLORS;
	}

	void SpriteEntry::setTopColor(Color &color)
	{
		setTopLeftColor(color);
		setTopRightColor(color);
	}

	void SpriteEntry::setBotColor(Color &color)
	{
		setBotLeftColor(color);
		setBotRightColor(color);
	}

	void SpriteEntry::setLeftColor(Color &color)
	{
		setTopLeftColor(color);
		setBotLeftColor(color);
	}
	
	void SpriteEntry::setRightColor(Color &color)
	{
		setTopRightColor(color);
		setBotRightColor(color);
	}

	void SpriteEntry::setTopLeftColor(Color &color)
	{
		std::memcpy(&this->colors[0], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= UPDATE_COLORS;
	}

	void SpriteEntry::setTopRightColor(Color &color)
	{
		std::memcpy(&this->colors[4], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= UPDATE_COLORS;
	}

	void SpriteEntry::setBotLeftColor(Color &color)
	{
		std::memcpy(&this->colors[12], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= UPDATE_COLORS;
	}

	void SpriteEntry::setBotRightColor(Color &color)
	{
		std::memcpy(&this->colors[8], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= UPDATE_COLORS;
	}

	void SpriteEntry::setOpacity(float opacity)
	{
		if (this->opacity == opacity)
			return;
		this->opacity = opacity;
		this->updatesRequired |= UPDATE_COLORS;
	}

	void SpriteEntry::setScaleX(float scaleX)
	{
		if (this->scaleX == scaleX)
			return;
		this->scaleX = scaleX;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void SpriteEntry::setScaleY(float scaleY)
	{
		if (this->scaleY == scaleY)
			return;
		this->scaleY = scaleY;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void SpriteEntry::setTexX(float texX)
	{
		this->texCoords[0] = texX;
		this->texCoords[6] = texX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexY(float texY)
	{
		this->texCoords[1] = texY;
		this->texCoords[3] = texY;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexWidth(float texWidth)
	{
		this->texCoords[2] = texWidth;
		this->texCoords[4] = texWidth;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexHeight(float texHeight)
	{
		this->texCoords[5] = texHeight;
		this->texCoords[7] = texHeight;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setWidth(float width)
	{
		this->vertex[2] = width;
		this->vertex[4] = width;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void SpriteEntry::setHeight(float height)
	{
		this->vertex[5] = height;
		this->vertex[7] = height;
		this->updatesRequired |= UPDATE_VERTEX;
	}

}
