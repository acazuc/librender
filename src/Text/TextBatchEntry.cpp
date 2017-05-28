#include "TextBatchEntry.h"
#include "TextBatch.h"

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

namespace librender
{

	TextBatchEntry::TextBatchEntry()
	: TextEntry()
	, parent(NULL)
	{
		//Empty
	}

	TextBatchEntry::~TextBatchEntry()
	{
		//Empty
	}

	void TextBatchEntry::resize(uint32_t len)
	{
		if (this->parent)
			this->parent->setMustResize(true);
		TextEntry::resize(len);
	}

	void TextBatchEntry::update()
	{
		uint8_t oldUpdates = this->updatesRequired;
		TextEntry::update();
		this->changes = this->updatesRequired | oldUpdates;
		if (this->changes & UPDATE_VERTEX)
		{
			for (uint32_t i = 0; i < this->verticesNumber; ++i)
			{
				this->vertex[i * 2 + 0] += this->x;
				this->vertex[i * 2 + 1] += this->y;
			}
		}
		if (this->changes)
			this->parent->addChanges(this->changes);
	}

	void TextBatchEntry::setParent(TextBatch *textBatch)
	{
		if (this->parent && (!textBatch || this->parent->getFont() != textBatch->getFont()))
		{
			this->updatesRequired |= UPDATE_VERTEX;
			this->updatesRequired |= UPDATE_TEX_COORDS;
			this->updatesRequired |= UPDATE_COLORS;
		}
		this->parent = textBatch;
	}

	Font *TextBatchEntry::getFont()
	{
		if (this->parent)
			return (this->parent->getFont());
		return (NULL);
	}

	void TextBatchEntry::setX(float x)
	{
		if (x == this->x)
			return;
		float diffX = x - this->x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertex[i * 2] += diffX;
		this->x = x;
	}

	void TextBatchEntry::setY(float y)
	{
		if (y == this->y)
			return;
		float diffY = y - this->y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertex[i * 2 + 1] += diffY;
		this->y = y;
	}

}
