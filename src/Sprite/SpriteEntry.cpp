#include "SpriteEntry.h"

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

namespace librender
{

	SpriteEntry::SpriteEntry()
	: color(Color::WHITE)
	, verticesNumber(0)
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
		//Empty
	}

	void SpriteEntry::fillVertex(GLfloat *vertex)
	{
		//Empty
	}

	void SpriteEntry::fillColors(GLfloat *colors)
	{
		//Empty
	}

	void SpriteEntry::update()
	{
		if (!getTexture())
			return;
		if (this->updatesRequired & UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & UPDATE_VERTEX)
			updateVertex();
		if (this->updatesRequired & UPDATE_COLORS)
			updateColors();
		this->updatesRequired = 0;
	}

	void SpriteEntry::setColor(Color &color)
	{
		if (!color.compare(this->color))
			return;
		this->color = color;
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

}
