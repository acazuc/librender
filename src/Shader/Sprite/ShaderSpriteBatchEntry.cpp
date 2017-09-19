#include "ShaderSpriteBatchEntry.h"
#include "./ShaderSpriteUpdate.h"
#include "./ShaderSpriteBatch.h"

namespace librender
{

	ShaderSpriteBatchEntry::ShaderSpriteBatchEntry()
	: ShaderSpriteEntry()
	, parent(NULL)
	, changes(0)
	{
		//Empty
	}

	ShaderSpriteBatchEntry::~ShaderSpriteBatchEntry()
	{
		if (this->parent)
			this->parent->removeEntry(this);
	}

	void ShaderSpriteBatchEntry::update()
	{
		uint8_t oldUpdates = this->updatesRequired;
		ShaderSpriteEntry::update();
		this->changes = this->updatesRequired | oldUpdates;
		this->parent->addChanges(this->changes);
	}

	void ShaderSpriteBatchEntry::setParent(ShaderSpriteBatch *spriteBatch)
	{
		if (this->parent && (!spriteBatch || this->parent->getTexture() != spriteBatch->getTexture()))
		{
			this->updatesRequired |= SHADER_SPRITE_UPDATE_VERTEXES;
			this->updatesRequired |= SHADER_SPRITE_UPDATE_TEX_COORDS;
			this->updatesRequired |= SHADER_SPRITE_UPDATE_COLORS;
		}
		this->parent = spriteBatch;
	}

	Texture *ShaderSpriteBatchEntry::getTexture()
	{
		if (this->parent)
			return (this->parent->getTexture());
		return (NULL);
	}

	void ShaderSpriteBatchEntry::setX(float x)
	{
		if (this->x == x)
			return;
		float delta = x - this->x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertex[i * 2] += delta;
		this->x = x;
		this->updatesRequired |= SHADER_SPRITE_UPDATE_VERTEXES;
	}

	void ShaderSpriteBatchEntry::setY(float y)
	{
		if (this->y == y)
			return;
		float delta = y - this->y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertex[i * 2 + 1] += delta;
		this->y = y;
		this->updatesRequired |= SHADER_SPRITE_UPDATE_VERTEXES;
	}
	
	void ShaderSpriteBatchEntry::setWidth(float width)
	{
		float delta = width - (this->vertex[2] - this->x);
		if (!delta)
			return;
		this->vertex[2] = width + this->x;
		this->vertex[4] = width + this->x;
		this->updatesRequired |= SHADER_SPRITE_UPDATE_VERTEXES;
	}

	void ShaderSpriteBatchEntry::setHeight(float height)
	{
		float delta = height - (this->vertex[7] - this->y);
		if (!delta)
			return;
		this->vertex[5] = height + this->y;
		this->vertex[7] = height + this->y;
		this->updatesRequired |= SHADER_SPRITE_UPDATE_VERTEXES;
	}

}
