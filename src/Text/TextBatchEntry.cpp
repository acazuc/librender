#include "TextBatchEntry.h"
#include "./TextUpdate.h"
#include "./TextBatch.h"

namespace librender
{

	TextBatchEntry::TextBatchEntry()
	: parent(nullptr)
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

	void TextBatchEntry::requireUpdates(uint8_t updates)
	{
		TextEntry::requireUpdates(updates);
		addChanges(updates);
		if (this->parent)
			this->parent->addChanges(updates);
	}

	void TextBatchEntry::update()
	{
		TextEntry::update();
		if (this->changes & TEXT_UPDATE_VERTEXES && (this->pos.x || this->pos.y || this->scale.x || this->scale.y))
		{
			for (uint32_t i = 0; i < this->verticesNumber; ++i)
			{
				this->vertexes[i] *= this->scale;
				this->vertexes[i] += this->pos;
			}
		}
	}

	void TextBatchEntry::setParent(TextBatch *textBatch)
	{
		if (this->parent && (!textBatch || this->parent->getFont() != textBatch->getFont()))
			requireUpdates(TEXT_UPDATE_VERTEXES | TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_COLORS);
		this->parent = textBatch;
	}

	Font *TextBatchEntry::getFont()
	{
		if (this->parent)
			return (this->parent->getFont());
		return (nullptr);
	}

	void TextBatchEntry::setX(float x)
	{
		if (this->pos.x == x)
			return;
		float diffX = x - this->pos.x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i].x += diffX;
		this->pos.x = x;
	}

	void TextBatchEntry::setY(float y)
	{
		if (this->pos.y == y)
			return;
		float diffY = y - this->pos.y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i].y += diffY;
		this->pos.y = y;
	}

	void TextBatchEntry::setScaleX(float scaleX)
	{
		if (this->scale.x == scaleX)
			return;
		float ratioX = scaleX / this->scale.x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i].x *= ratioX;
		this->scale.x = scaleX;
	}

	void TextBatchEntry::setScaleY(float scaleY)
	{
		if (this->scale.y == scaleY)
			return;
		float ratioY = scaleY / this->scale.y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i].y *= ratioY;
		this->scale.y = scaleY;
	}

}
