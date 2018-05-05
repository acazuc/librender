#include "SpriteBatchEntry.h"
#include "./SpriteUpdate.h"
#include "./SpriteBatch.h"

namespace librender
{

	SpriteBatchEntry::SpriteBatchEntry()
	: SpriteEntry()
	, parent(nullptr)
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
		return (nullptr);
	}

	void SpriteBatchEntry::setX(float x)
	{
		if (this->pos.x == x)
			return;
		float delta = x - this->pos.x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i].x += delta;
		this->pos.x = x;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	float SpriteBatchEntry::getX()
	{
		if (!this->parent)
			return (0);
		return (this->parent->getX() + this->pos.x);
	}

	void SpriteBatchEntry::setY(float y)
	{
		if (this->pos.y == y)
			return;
		float delta = y - this->pos.y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i].y += delta;
		this->pos.y = y;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	float SpriteBatchEntry::getY()
	{
		if (!this->parent)
			return (0);
		return (this->parent->getY() + this->pos.y);
	}
	
	void SpriteBatchEntry::setWidth(float width)
	{
		float delta = width - (this->vertexes[1].x - this->pos.x);
		if (!delta)
			return;
		this->vertexes[1].x = width + this->pos.x;
		this->vertexes[2].x = width + this->pos.x;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

	void SpriteBatchEntry::setHeight(float height)
	{
		float delta = height - (this->vertexes[3].y - this->pos.y);
		if (!delta)
			return;
		this->vertexes[2].y = height + this->pos.y;
		this->vertexes[3].y = height + this->pos.y;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
	}

}
