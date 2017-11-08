#include "SpriteEntry.h"
#include "./SpriteUpdate.h"
#include "../GL.h"
#include <cstring>

namespace librender
{

	SpriteEntry::SpriteEntry()
	: verticesNumber(4)
	, updatesRequired(0)
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
			vertexes[i] = 0;
	}

	SpriteEntry::~SpriteEntry()
	{
		//Empty
	}

	void SpriteEntry::fillTexCoords(GLfloat *texCoords)
	{
		std::memcpy(texCoords, this->texCoords, sizeof(this->texCoords));
	}

	void SpriteEntry::fillVertexes(GLfloat *vertexes)
	{
		std::memcpy(vertexes, this->vertexes, sizeof(this->vertexes));
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
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setTopRightColor(Color &color)
	{
		std::memcpy(&this->colors[4], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setBotLeftColor(Color &color)
	{
		std::memcpy(&this->colors[12], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setBotRightColor(Color &color)
	{
		std::memcpy(&this->colors[8], &color, sizeof(*this->colors) * 4);
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setScaleX(float scaleX)
	{
		if (this->scaleX == scaleX)
			return;
		this->scaleX = scaleX;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteEntry::setScaleY(float scaleY)
	{
		if (this->scaleY == scaleY)
			return;
		this->scaleY = scaleY;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteEntry::setTexX(float texX)
	{
		float delta = texX - this->texCoords[0];
		if (!delta)
			return;
		this->texCoords[0] = texX;
		this->texCoords[6] = texX;
		this->texCoords[2] += delta;
		this->texCoords[4] += delta;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexY(float texY)
	{
		float delta = texY - this->texCoords[1];
		if (!delta)
			return;
		this->texCoords[1] = texY;
		this->texCoords[3] = texY;
		this->texCoords[5] += delta;
		this->texCoords[7] += delta;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexPos(float texX, float texY)
	{
		setTexX(texX);
		setTexY(texY);
	}

	void SpriteEntry::setTexWidth(float texWidth)
	{
		float delta = texWidth - (this->texCoords[2] - this->texCoords[0]);
		if (!delta)
			return;
		this->texCoords[2] = texWidth + this->texCoords[0];
		this->texCoords[4] = texWidth + this->texCoords[0];
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexHeight(float texHeight)
	{
		float delta = texHeight - (this->texCoords[7] - this->texCoords[1]);
		if (!delta)
			return;
		this->texCoords[5] = texHeight + this->texCoords[1];
		this->texCoords[7] = texHeight + this->texCoords[1];
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexSize(float texWidth, float texHeight)
	{
		setTexWidth(texWidth);
		setTexHeight(texHeight);
	}

	void SpriteEntry::setWidth(float width)
	{
		float delta = width - (this->vertexes[2] - this->vertexes[0]);
		if (!delta)
			return;
		this->vertexes[2] = width;
		this->vertexes[4] = width;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteEntry::setHeight(float height)
	{
		float delta = height - (this->vertexes[7] - this->vertexes[1]);
		if (!delta)
			return;
		this->vertexes[5] = height;
		this->vertexes[7] = height;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteEntry::setSize(float width, float height)
	{
		setWidth(width);
		setHeight(height);
	}

	int32_t SpriteEntry::getTextureWidth()
	{
		if (!getTexture())
			return (0);
		return (getTexture()->getWidth());
	}

	int32_t SpriteEntry::getTextureHeight()
	{
		if (!getTexture())
			return (0);
		return (getTexture()->getHeight());
	}

}
