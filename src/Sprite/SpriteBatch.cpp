#include "SpriteBatch.h"
#include "./SpriteUpdate.h"
#include "../GL.h"
#include <cstring>

namespace librender
{

	SpriteBatch::SpriteBatch()
	: texture(NULL)
	, texCoords(NULL)
	, vertexes(NULL)
	, colors(NULL)
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
			this->entries[i]->setParent(NULL);
		delete[] (this->texCoords);
		delete[] (this->vertexes);
		delete[] (this->colors);
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
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * sizeof(*this->texCoords));
				entry->removeChange(SPRITE_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber();
		}
	}

	void SpriteBatch::updateVertex()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			SpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SPRITE_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertexes(), entry->getVerticesNumber() * sizeof(*this->vertexes));
				entry->removeChange(SPRITE_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber();
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
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * sizeof(*this->colors));
				entry->removeChange(SPRITE_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber();
		}
	}

	void SpriteBatch::resize()
	{
		updateVerticesNumber();
		if (!this->verticesNumber)
			return;
		delete[] (this->texCoords);
		this->texCoords = new Vec2[std::max(1u, this->verticesNumber)];
		delete[] (this->vertexes);
		this->vertexes = new Vec2[std::max(1u, this->verticesNumber)];
		delete[] (this->colors);
		this->colors = new Vec4[std::max(1u, this->verticesNumber)];
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
			this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
		if (this->changes & SPRITE_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & SPRITE_UPDATE_VERTEXES)
			updateVertex();
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
		glColorPointer(4, GL_FLOAT, 0, this->colors);
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes);
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords);
		glPushMatrix();
		glTranslatef(this->pos.x, this->pos.y, 0);
		glDrawArrays(GL_QUADS, 0, this->verticesNumber);
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
		entry->setParent(NULL);
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			if (this->entries[i] == entry)
			{
				this->entries.erase(this->entries.begin() + i);
				this->mustResize = true;
				this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
				return;
			}
		}
	}

	void SpriteBatch::setTexture(Texture *texture)
	{
		this->texture = texture;
		this->changes = SPRITE_UPDATE_TEX_COORDS | SPRITE_UPDATE_VERTEXES | SPRITE_UPDATE_COLORS;
	}

}
