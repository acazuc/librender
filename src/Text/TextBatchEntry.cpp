#include "TextBatchEntry.h"
#include "./TextUpdate.h"
#include "./TextBatch.h"

namespace librender
{

	TextBatchEntry::TextBatchEntry()
	: TextEntry()
	, parent(NULL)
	, changes(0)
	{
		//Empty
	}

	TextBatchEntry::~TextBatchEntry()
	{
		if (this->parent)
			this->parent->removeEntry(this);
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
		if (this->changes & TEXT_UPDATE_VERTEXES && (this->x || this->y || this->scaleX || this->scaleY))
		{
			for (uint32_t i = 0; i < this->verticesNumber; ++i)
			{
				this->vertexes[i * 2 + 0] *= this->scaleX;
				this->vertexes[i * 2 + 1] *= this->scaleY;
				this->vertexes[i * 2 + 0] += this->x;
				this->vertexes[i * 2 + 1] += this->y;
			}
		}
		if (this->changes)
			this->parent->addChanges(this->changes);
	}

	void TextBatchEntry::setParent(TextBatch *textBatch)
	{
		if (this->parent && (!textBatch || this->parent->getFont() != textBatch->getFont()))
		{
			this->updatesRequired |= TEXT_UPDATE_VERTEXES;
			this->updatesRequired |= TEXT_UPDATE_TEX_COORDS;
			this->updatesRequired |= TEXT_UPDATE_COLORS;
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
		if (this->x == x)
			return;
		float diffX = x - this->x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2] += diffX;
		this->x = x;
	}

	void TextBatchEntry::setY(float y)
	{
		if (this->y == y)
			return;
		float diffY = y - this->y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2 + 1] += diffY;
		this->y = y;
	}

	void TextBatchEntry::setScaleX(float scaleX)
	{
		if (this->scaleX == scaleX)
			return;
		float ratioX = scaleX / this->scaleX;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2] *= ratioX;
		this->scaleX = scaleX;
	}

	void TextBatchEntry::setScaleY(float scaleY)
	{
		if (this->scaleY == scaleY)
			return;
		float ratioY = scaleY / this->scaleY;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2 + 1] *= ratioY;
		this->scaleY = scaleY;
	}

}
