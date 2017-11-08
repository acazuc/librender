#include "ShaderTextBatchEntry.h"
#include "./ShaderTextUpdate.h"
#include "./ShaderTextBatch.h"

namespace librender
{

	ShaderTextBatchEntry::ShaderTextBatchEntry()
	: ShaderTextEntry()
	, parent(NULL)
	, changes(0)
	{
		//Empty
	}

	ShaderTextBatchEntry::~ShaderTextBatchEntry()
	{
		if (this->parent)
			this->parent->removeEntry(this);
	}

	void ShaderTextBatchEntry::resize(uint32_t len)
	{
		if (this->parent)
			this->parent->setMustResize(true);
		ShaderTextEntry::resize(len);
	}

	void ShaderTextBatchEntry::update()
	{
		uint8_t oldUpdates = this->updatesRequired;
		ShaderTextEntry::update();
		this->changes = this->updatesRequired | oldUpdates;
		if (this->changes & SHADER_TEXT_UPDATE_VERTEXES && (this->x || this->y || this->scaleX || this->scaleY))
		{
			for (uint32_t i = 0; i < this->verticesNumber; ++i)
			{
				this->vertexes[i * 2 + 0] *= this->scaleX;
				this->vertexes[i * 2 + 0] *= this->scaleY;
				this->vertexes[i * 2 + 0] += this->x;
				this->vertexes[i * 2 + 1] += this->y;
			}
		}
		if (this->changes)
			this->parent->addChanges(this->changes);
	}

	void ShaderTextBatchEntry::setParent(ShaderTextBatch *textBatch)
	{
		if (this->parent && (!textBatch || this->parent->getFont() != textBatch->getFont()))
		{
			this->updatesRequired |= SHADER_TEXT_UPDATE_VERTEXES;
			this->updatesRequired |= SHADER_TEXT_UPDATE_TEX_COORDS;
			this->updatesRequired |= SHADER_TEXT_UPDATE_COLORS;
		}
		this->parent = textBatch;
	}

	Font *ShaderTextBatchEntry::getFont()
	{
		if (this->parent)
			return (this->parent->getFont());
		return (NULL);
	}

	void ShaderTextBatchEntry::setX(float x)
	{
		if (this->x == x)
			return;
		float diffX = x - this->x;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2] += diffX;
		this->x = x;
	}

	void ShaderTextBatchEntry::setY(float y)
	{
		if (this->y == y)
			return;
		float diffY = y - this->y;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2 + 1] += diffY;
		this->y = y;
	}

	void ShaderTextBatchEntry::setScaleX(float scaleX)
	{
		if (this->scaleX == scaleX)
			return;
		float ratioX = scaleX / this->scaleX;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2] *= ratioX;
		this->scaleX = scaleX;
	}

	void ShaderTextBatchEntry::setScaleY(float scaleY)
	{
		if (this->scaleY == scaleY)
			return;
		float ratioY = scaleY / this->scaleY;
		for (uint32_t i = 0; i < this->verticesNumber; ++i)
			this->vertexes[i * 2 + 1] *= ratioY;
		this->scaleY = scaleY;
	}

}
