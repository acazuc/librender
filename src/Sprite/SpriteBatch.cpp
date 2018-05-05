#include "SpriteBatch.h"
#include "./SpriteUpdate.h"
#include "../GL.h"
#include <cstring>

namespace librender
{

	SpriteBatch::SpriteBatch()
	: texture(nullptr)
	, pos(0)
	, verticesNumber(0)
	, changes(0)
	, mustResize(true)
	{
		//Empty
	}

	SpriteBatch::~SpriteBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(nullptr);
	}

	void SpriteBatch::updateVerticesNumber()
	{
		this->verticesNumber = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->verticesNumber += this->entries[i]->getVerticesNumber();
	}

	void SpriteBatch::updateTexCoords()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			SpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SPRITE_UPDATE_TEX_COORDS)
			{
				std::memcpy(&this->texCoords[count], entry->getTexCoords().data(), entry->getVerticesNumber() * sizeof(*this->texCoords.data()));
				entry->removeChange(SPRITE_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber();
		}
	}

	void SpriteBatch::updateVertexes()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			SpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SPRITE_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertexes().data(), entry->getVerticesNumber() * sizeof(*this->vertexes.data()));
				entry->removeChange(SPRITE_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber();
		}
	}

	void SpriteBatch::updateIndices()
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

	void SpriteBatch::updateColors()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			SpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SPRITE_UPDATE_COLORS)
			{
				std::memcpy(&this->colors[count], entry->getColors().data(), entry->getVerticesNumber() * sizeof(*this->colors.data()));
				entry->removeChange(SPRITE_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber();
		}
	}

	void SpriteBatch::resize()
	{
		updateVerticesNumber();
		this->texCoords.resize(this->verticesNumber);
		this->vertexes.resize(this->verticesNumber);
		this->indices.resize(this->verticesNumber / 4 * 6);
		this->colors.resize(this->verticesNumber);
	}

	void SpriteBatch::draw()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->update();
		if (this->mustResize)
			resize();
		if (!this->verticesNumber)
			return;
		if (this->mustResize)
		{
			this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
			updateIndices();
		}
		if (this->changes & SPRITE_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & SPRITE_UPDATE_VERTEXES)
			updateVertexes();
		if (this->changes & SPRITE_UPDATE_COLORS)
			updateColors();
		if (this->mustResize)
			this->mustResize = false;
		this->changes = 0;
		if (this->texture)
			this->texture->bind();
		else
			glBindTexture(GL_TEXTURE_2D, 0);
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

	void SpriteBatch::addEntry(SpriteBatchEntry *entry)
	{
		entry->setParent(this);
		this->entries.push_back(entry);
		this->mustResize = true;
		this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
	}

	void SpriteBatch::removeEntry(SpriteBatchEntry *entry)
	{
		entry->setParent(nullptr);
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			if (this->entries[i] != entry)
				continue;
			this->entries.erase(this->entries.begin() + i);
			this->mustResize = true;
			this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
			return;
		}
	}

	void SpriteBatch::setTexture(Texture *texture)
	{
		this->texture = texture;
		this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
	}

}
