#include "TextBatch.h"
#include "./TextUpdate.h"
#include "../GL.h"
#include <cstring>

namespace librender
{

	TextBatch::TextBatch()
	: texCoords(NULL)
	, vertex(NULL)
	, colors(NULL)
	, font(NULL)
	, verticesNumber(0)
	, changes(0)
	, x(0)
	, y(0)
	, mustResize(true)
	{
		//Empty
	}

	TextBatch::~TextBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
		delete[] (this->texCoords);
		delete[] (this->vertex);
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
			if (this->mustResize || entry->getChanges() & TEXT_UPDATE_TEX_COORDS)
			{
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * 2 * sizeof(*this->texCoords));
				entry->removeChanges(TEXT_UPDATE_TEX_COORDS);
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
			if (this->mustResize || entry->getChanges() & TEXT_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertex[count], entry->getVertex(), entry->getVerticesNumber() * 2 * sizeof(*this->vertex));
				entry->removeChanges(TEXT_UPDATE_VERTEXES);
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
			if (this->mustResize || entry->getChanges() & TEXT_UPDATE_COLORS)
			{
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * 4 * sizeof(*this->colors));
				entry->removeChanges(TEXT_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber() * 4;
		}
	}

	void TextBatch::resize()
	{
		updateVerticesNumber();
		if (!this->verticesNumber)
			return;
		delete[] (this->texCoords);
		this->texCoords = new GLfloat[this->verticesNumber * 2 + 1];
		delete[] (this->vertex);
		this->vertex = new GLfloat[this->verticesNumber * 2 + 1];
		delete[] (this->colors);
		this->colors = new GLfloat[this->verticesNumber * 4 + 1];
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
			this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES | TEXT_UPDATE_COLORS;
		if (this->changes & TEXT_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & TEXT_UPDATE_VERTEXES)
			updateVertex();
		if (this->changes & TEXT_UPDATE_COLORS)
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
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			if (this->entries[i] == entry)
			{
				this->entries.erase(this->entries.begin() + i);
				entry->setParent(NULL);
				return;
			}
		}
	}

	void TextBatch::clearEntries()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
		this->entries.clear();
	}

	void TextBatch::setFont(Font *font)
	{
		this->font = font;
		this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->addChanges(TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES);
	}

}
