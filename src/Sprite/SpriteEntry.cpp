#include "SpriteEntry.h"
#include "./SpriteUpdate.h"
#include <cstring>

namespace librender
{

	SpriteEntry::SpriteEntry()
	: texCoords(4)
	, vertexes(4)
	, colors(4)
	, scale(1)
	, pos(0)
	, verticesNumber(4)
	, updatesRequired(0)
	{
		texCoords[0] = Vec2(0, 0);
		texCoords[1] = Vec2(1, 0);
		texCoords[2] = Vec2(1, 1);
		texCoords[3] = Vec2(0, 1);
		for (uint8_t i = 0; i < 4; ++i)
			colors[i] = Vec4(1);
		for (uint8_t i = 0; i < 4; ++i)
			vertexes[i] = Vec2(0);
	}

	SpriteEntry::~SpriteEntry()
	{
		//Empty
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
		std::memcpy(&this->colors[0], &color, sizeof(*this->colors.data()));
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setTopRightColor(Color &color)
	{
		std::memcpy(&this->colors[1], &color, sizeof(*this->colors.data()));
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setBotLeftColor(Color &color)
	{
		std::memcpy(&this->colors[3], &color, sizeof(*this->colors.data()));
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setBotRightColor(Color &color)
	{
		std::memcpy(&this->colors[2], &color, sizeof(*this->colors.data()));
		this->updatesRequired |= SPRITE_UPDATE_COLORS;
	}

	void SpriteEntry::setScaleX(float scaleX)
	{
		if (this->scale.x == scaleX)
			return;
		this->scale.x = scaleX;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteEntry::setScaleY(float scaleY)
	{
		if (this->scale.y == scaleY)
			return;
		this->scale.y = scaleY;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteEntry::setTexX(float texX)
	{
		float delta = texX - this->texCoords[0].x;
		if (!delta)
			return;
		this->texCoords[0].x = texX;
		this->texCoords[3].x = texX;
		this->texCoords[1].x += delta;
		this->texCoords[2].x += delta;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexY(float texY)
	{
		float delta = texY - this->texCoords[0].y;
		if (!delta)
			return;
		this->texCoords[0].y = texY;
		this->texCoords[1].y = texY;
		this->texCoords[2].y += delta;
		this->texCoords[3].y += delta;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexPos(float texX, float texY)
	{
		setTexX(texX);
		setTexY(texY);
	}

	void SpriteEntry::setTexWidth(float texWidth)
	{
		float delta = texWidth - (this->texCoords[1].x - this->texCoords[0].x);
		if (!delta)
			return;
		this->texCoords[1].x = texWidth + this->texCoords[0].x;
		this->texCoords[2].x = texWidth + this->texCoords[0].x;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexHeight(float texHeight)
	{
		float delta = texHeight - (this->texCoords[3].y - this->texCoords[0].y);
		if (!delta)
			return;
		this->texCoords[2].y = texHeight + this->texCoords[0].y;
		this->texCoords[3].y = texHeight + this->texCoords[0].y;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

	void SpriteEntry::setTexSize(float texWidth, float texHeight)
	{
		setTexWidth(texWidth);
		setTexHeight(texHeight);
	}

	void SpriteEntry::setWidth(float width)
	{
		float delta = width - (this->vertexes[1].x - this->vertexes[0].x);
		if (!delta)
			return;
		this->vertexes[1].x = width;
		this->vertexes[2].x = width;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	float SpriteEntry::getWidth()
	{
		return (this->vertexes[1].x - this->vertexes[0].x);
	}

	void SpriteEntry::setHeight(float height)
	{
		float delta = height - (this->vertexes[3].y - this->vertexes[0].y);
		if (!delta)
			return;
		this->vertexes[2].y = height;
		this->vertexes[3].y = height;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	float SpriteEntry::getHeight()
	{
		return (this->vertexes[2].y - this->vertexes[1].y);
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
