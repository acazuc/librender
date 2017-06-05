#include "SpriteBatchEntry.h"
#include "SpriteBatch.h"

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

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
		//Empty
	}

	void SpriteBatchEntry::update()
	{
		uint8_t oldUpdates = this->updatesRequired;
		SpriteEntry::update();
		this->changes = this->updatesRequired | oldUpdates;
		if (this->changes & UPDATE_VERTEX && (this->x || this->y))
		{
			for (uint32_t i = 0; i < this->verticesNumber; ++i)
			{
				this->vertex[i * 2 + 0] += this->x;
				this->vertex[i * 2 + 1] += this->y;
			}
		}
		this->parent->addChanges(this->changes);
	}

	void SpriteBatchEntry::setParent(SpriteBatch *spriteBatch)
	{
		if (this->parent && (!spriteBatch || this->parent->getTexture() != spriteBatch->getTexture()))
		{
			this->updatesRequired |= UPDATE_VERTEX;
			this->updatesRequired |= UPDATE_TEX_COORDS;
			this->updatesRequired |= UPDATE_COLORS;
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
		this->x = x;
		this->updatesRequired |= UPDATE_VERTEX;
	}

	void SpriteBatchEntry::setY(float y)
	{
		if (this->y == y)
			return;
		this->y = y;
		this->updatesRequired |= UPDATE_VERTEX;
	}

}
