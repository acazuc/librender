#include "SpriteBatchEntry.h"
#include "./SpriteUpdate.h"
#include "./SpriteBatch.h"

namespace librender
{

	SpriteBatchEntry::SpriteBatchEntry()
	: SpriteEntry()
	, parent(NULL)
	, changes(0)
	{
		//Empty
	}

	SpriteBatchEntry::~SpriteBatchEntry()
	{
		if (this->parent)
			this->parent->removeEntry(this);
	}

	void SpriteBatchEntry::update()
	{
		uint8_t oldUpdates = this->updatesRequired;
		SpriteEntry::update();
		this->changes = this->updatesRequired | oldUpdates;
		this->parent->addChanges(this->changes);
	}

	void SpriteBatchEntry::setParent(SpriteBatch *spriteBatch)
	{
		if (this->parent && (!spriteBatch || this->parent->getTexture() != spriteBatch->getTexture()))
		{
			this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
			this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
			this->updatesRequired |= SPRITE_UPDATE_COLORS;
		}
		this->parent = spriteBatch;
	}

	Texture *SpriteBatchEntry::getTexture()
	{
		if (this->parent)
			return (this->parent->getTexture());
		return (NULL);
	}

	void SpriteBatchEntry::setX(float x)
	{
		if (this->x == x)
			return;
		float delta = x - this->x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2] += delta;
		this->x = x;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteBatchEntry::setY(float y)
	{
		if (this->y == y)
			return;
		float delta = y - this->y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2 + 1] += delta;
		this->y = y;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}
	
	void SpriteBatchEntry::setWidth(float width)
	{
		float delta = width - (this->vertexes[2] - this->x);
		if (!delta)
			return;
		this->vertexes[2] = width + this->x;
		this->vertexes[4] = width + this->x;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteBatchEntry::setHeight(float height)
	{
		float delta = height - (this->vertexes[7] - this->y);
		if (!delta)
			return;
		this->vertexes[5] = height + this->y;
		this->vertexes[7] = height + this->y;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

}
