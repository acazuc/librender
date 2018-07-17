#include "TextBatch.h"
#include "./TextUpdate.h"
#include "../GL.h"
#include <cstring>

namespace librender
{

	TextBatch::TextBatch()
	: font(nullptr)
	, pos(0)
	, verticesNumber(0)
	, changes(0)
	, mustResize(true)
	{
		//Empty
	}

	TextBatch::~TextBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(nullptr);
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
				std::memcpy(&this->texCoords[count], entry->getTexCoords().data(), entry->getVerticesNumber() * sizeof(*this->texCoords.data()));
				entry->removeChanges(TEXT_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber();
		}
	}

	void TextBatch::updateVertexes()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			TextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & TEXT_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertexes().data(), entry->getVerticesNumber() * sizeof(*this->vertexes.data()));
				entry->removeChanges(TEXT_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber();
		}
	}

	void TextBatch::updateIndices()
	{
		uint32_t count = 0;
		GLuint currentIndice = 0;
		for (uint32_t i = 0; i < this->verticesNumber / 4; ++i)
		{
			indices[count++] = currentIndice + 0;
			indices[count++] = currentIndice + 3;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 2;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 3;
			currentIndice += 4;
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
				std::memcpy(&this->colors[count], entry->getColors().data(), entry->getVerticesNumber() * sizeof(*this->colors.data()));
				entry->removeChanges(TEXT_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber();
		}
	}

	void TextBatch::resize()
	{
		updateVerticesNumber();
		this->texCoords.resize(this->verticesNumber);
		this->vertexes.resize(this->verticesNumber);
		this->indices.resize(this->verticesNumber / 4 * 6);
		this->colors.resize(this->verticesNumber);
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
		{
			this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES | TEXT_UPDATE_COLORS;
			updateIndices();
		}
		if (this->changes & TEXT_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & TEXT_UPDATE_VERTEXES)
			updateVertexes();
		if (this->changes & TEXT_UPDATE_COLORS)
			updateColors();
		if (this->mustResize)
			this->mustResize = false;
		this->changes = 0;
		this->font->bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors.data());
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes.data());
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords.data());
		glPushMatrix();
		glTranslatef(this->pos.x, this->pos.y, 0);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, this->indices.data());
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void TextBatch::addEntry(TextBatchEntry *entry)
	{
		entry->setParent(this);
		this->entries.push_back(entry);
		this->mustResize = true;
		this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES | TEXT_UPDATE_COLORS;
	}

	void TextBatch::removeEntry(TextBatchEntry *entry)
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			if (this->entries[i] == entry)
			{
				this->entries.erase(this->entries.begin() + i);
				entry->setParent(nullptr);
				this->mustResize = true;
				this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES | TEXT_UPDATE_COLORS;
				return;
			}
		}
	}

	void TextBatch::clearEntries()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(nullptr);
		this->entries.clear();
		this->mustResize = true;
		this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES | TEXT_UPDATE_COLORS;
	}

	void TextBatch::setFont(Font *font)
	{
		this->font = font;
		this->changes = TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			TextBatchEntry *entry = this->entries[i];
			entry->addChanges(TEXT_UPDATE_TEX_COORDS | TEXT_UPDATE_VERTEXES);
			entry->recalcWidth();
			entry->recalcHeight();
		}
	}

	int32_t TextBatch::getLineHeight()
	{
		if (!this->font)
			return 0;
		return this->font->getLineHeight();
	}

}
