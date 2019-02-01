#include "SpriteBase.h"
#include "../DrawableBuffers.h"
#include <cstring>
#include <iostream>

namespace librender
{

	SpriteBase::SpriteBase()
	: size(0)
	{
		setVerticesNumber(4);
		setIndicesNumber(6);
		this->texTopLeft = Vec2(0, 0);
		this->texBotRight = Vec2(1, 1);
		std::fill(this->colors.begin(), this->colors.end(), Vec4(1));
	}

	void SpriteBase::fillIndices(std::vector<uint32_t>::iterator indices)
	{
		indices[0] = 0;
		indices[1] = 3;
		indices[2] = 1;
		indices[3] = 1;
		indices[4] = 3;
		indices[5] = 2;
	}

	void SpriteBase::fillTexCoords(std::vector<Vec2>::iterator texCoords)
	{
		texCoords[0] = Vec2(this->texTopLeft.x, this->texTopLeft.y);
		texCoords[1] = Vec2(this->texBotRight.x, this->texTopLeft.y);
		texCoords[2] = Vec2(this->texBotRight.x, this->texBotRight.y);
		texCoords[3] = Vec2(this->texTopLeft.x, this->texBotRight.y);
	}

	void SpriteBase::fillVertexes(std::vector<Vec2>::iterator vertexes)
	{
		vertexes[0] = Vec2(0, 0);
		vertexes[1] = Vec2(this->size.x, 0);
		vertexes[2] = Vec2(this->size.x, this->size.y);
		vertexes[3] = Vec2(0, this->size.y);
	}

	void SpriteBase::fillColors(std::vector<Vec4>::iterator colors)
	{
		std::copy(this->colors.begin(), this->colors.end(), colors);
	}

	void SpriteBase::setColor(Color color)
	{
		setTopLeftColor(color);
		setTopRightColor(color);
		setBotLeftColor(color);
		setBotRightColor(color);
	}

	void SpriteBase::setTopColor(Color color)
	{
		setTopLeftColor(color);
		setTopRightColor(color);
	}

	void SpriteBase::setBotColor(Color color)
	{
		setBotLeftColor(color);
		setBotRightColor(color);
	}

	void SpriteBase::setLeftColor(Color color)
	{
		setTopLeftColor(color);
		setBotLeftColor(color);
	}
	
	void SpriteBase::setRightColor(Color color)
	{
		setTopRightColor(color);
		setBotRightColor(color);
	}

	void SpriteBase::setTopLeftColor(Color color)
	{
		this->colors[0] = color;
		requireUpdates(DRAWABLE_BUFFER_COLORS);
	}

	void SpriteBase::setTopRightColor(Color color)
	{
		this->colors[1] = color;
		requireUpdates(DRAWABLE_BUFFER_COLORS);
	}

	void SpriteBase::setBotLeftColor(Color color)
	{
		this->colors[3] = color;
		requireUpdates(DRAWABLE_BUFFER_COLORS);
	}

	void SpriteBase::setBotRightColor(Color color)
	{
		this->colors[2] = color;
		requireUpdates(DRAWABLE_BUFFER_COLORS);
	}

	void SpriteBase::setTexLeft(float left)
	{
		this->texTopLeft.x = left;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexRight(float right)
	{
		this->texBotRight.x = right;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexTop(float top)
	{
		this->texTopLeft.y = top;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexBot(float bot)
	{
		this->texBotRight.y = bot;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexTopBot(Vec2 topBot)
	{
		this->texTopLeft.y = topBot.x;
		this->texBotRight.y = topBot.y;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexLeftRight(Vec2 leftRight)
	{
		this->texTopLeft.x = leftRight.x;
		this->texBotRight.x = leftRight.y;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexTopLeft(Vec2 topLeft)
	{
		this->texTopLeft = topLeft;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setTexBotRight(Vec2 botRight)
	{
		this->texBotRight = botRight;
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS);
	}

	void SpriteBase::setWidth(float width)
	{
		if (this->size.x == width)
			return;
		this->size.x = width;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES);
	}

	float SpriteBase::getWidth()
	{
		return this->size.x * this->scale.x;
	}

	void SpriteBase::setHeight(float height)
	{
		if (this->size.y == height)
			return;
		this->size.y = height;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES);
	}

	float SpriteBase::getHeight()
	{
		return this->size.y * this->scale.y;
	}

	void SpriteBase::setSize(float width, float height)
	{
		setWidth(width);
		setHeight(height);
	}

	int32_t SpriteBase::getTextureWidth()
	{
		Texture *texture = getTexture();
		if (!texture)
			return 0;
		return texture->width;
	}

	int32_t SpriteBase::getTextureHeight()
	{
		Texture *texture = getTexture();
		if (!texture)
			return 0;
		return texture->height;
	}

}
