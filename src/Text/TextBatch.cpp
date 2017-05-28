#include "TextBatch.h"
#include <cstring>

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

namespace librender
{

	TextBatch::TextBatch()
	: texCoords(NULL)
	, vertex(NULL)
	, colors(NULL)
	, font(NULL)
	, verticesNumber(0)
	, x(0)
	, y(0)
	, changes(0)
	, mustResize(true)
	{
		//Empty
	}

	TextBatch::~TextBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
		if (this->texCoords)
			delete[] (this->texCoords);
		if (this->vertex)
			delete[] (this->vertex);
		if (this->colors)
			delete[] (this->colors);
	}

	void TextBatch::updateVerticesNumber()
	{
		this->verticesNumber = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->verticesNumber += this->entries[i]->getVerticesNumber();
	}

	void TextBatch::updateTexCoords()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			TextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & UPDATE_TEX_COORDS)
			{
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * 2 * sizeof(*this->texCoords));
				entry->removeChange(UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber() * 2;
		}
	}

	void TextBatch::updateVertex()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			TextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & UPDATE_VERTEX)
			{
				std::memcpy(&this->vertex[count], entry->getVertex(), entry->getVerticesNumber() * 2 * sizeof(*this->vertex));
				entry->removeChange(UPDATE_VERTEX);
			}
			count += entry->getVerticesNumber() * 2;
		}
	}

	void TextBatch::updateColors()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			TextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & UPDATE_COLORS)
			{
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * 4 * sizeof(*this->colors));
				entry->removeChange(UPDATE_COLORS);
			}
			count += entry->getVerticesNumber() * 4;
		}
	}

	void TextBatch::resize()
	{
		updateVerticesNumber();
		if (!this->verticesNumber)
			return;
		if (this->texCoords)
			delete[] (this->texCoords);
		this->texCoords = new float[this->verticesNumber * 2];
		if (this->vertex)
			delete[] (this->vertex);
		this->vertex = new float[this->verticesNumber * 2];
		if (this->colors)
			delete[] (this->colors);
		this->colors = new float[this->verticesNumber * 4];
	}

	void TextBatch::draw()
	{
		if (!this->font)
			return;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->update();
		if (this->mustResize)
			resize();
		if (!this->verticesNumber)
			return;
		if (this->mustResize)
			this->changes = UPDATE_TEX_COORDS | UPDATE_VERTEX | UPDATE_COLORS;
		if (this->changes & UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & UPDATE_VERTEX)
			updateVertex();
		if (this->changes & UPDATE_COLORS)
			updateColors();
		if (this->mustResize)
			this->mustResize = false;
		this->changes = 0;
		this->font->bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors);
		glVertexPointer(2, GL_FLOAT, 0, this->vertex);
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords);
		glPushMatrix();
		glTranslatef(this->x, this->y, 0);
		glDrawArrays(GL_QUADS, 0, this->verticesNumber);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void TextBatch::addEntry(TextBatchEntry *entry)
	{
		entry->setParent(this);
		this->entries.push_back(entry);
	}

	void TextBatch::removeEntry(TextBatchEntry *entry)
	{
		entry->setParent(NULL);
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			if (this->entries[i] == entry)
			{
				this->entries.erase(this->entries.begin() + i);
				return;
			}
		}
	}

	void TextBatch::setFont(Font *font)
	{
		this->font = font;
	}

}
