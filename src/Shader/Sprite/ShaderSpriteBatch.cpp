#include "ShaderSpriteBatch.h"
#include "./ShaderSpriteUpdate.h"
#include "../../GL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

namespace librender
{

	ShaderSpriteBatch::ShaderSpriteBatch()
	: texCoordsLocation(NULL)
	, vertexesLocation(NULL)
	, colorsLocation(NULL)
	, mvpLocation(NULL)
	, texture(NULL)
	, program(NULL)
	, verticesNumber(0)
	, changes(0)
	, x(0)
	, y(0)
	, mustResize(true)
	{
		//Empty
	}

	ShaderSpriteBatch::~ShaderSpriteBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
	}

	void ShaderSpriteBatch::updateVerticesNumber()
	{
		this->verticesNumber = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->verticesNumber += this->entries[i]->getVerticesNumber();
	}

	void ShaderSpriteBatch::updateTexCoords()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderSpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_SPRITE_UPDATE_TEX_COORDS)
			{
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * 2 * sizeof(*this->texCoords));
				entry->removeChange(SHADER_SPRITE_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber() * 2;
		}
		this->texCoordsBuffer.setData(GL_ARRAY_BUFFER, this->texCoords, count * sizeof(*this->texCoords) * 2, GL_FLOAT, 2, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::updateVertexes()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderSpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_SPRITE_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertex(), entry->getVerticesNumber() * 2 * sizeof(*this->vertexes));
				entry->removeChange(SHADER_SPRITE_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber() * 2;
		}
		this->vertexesBuffer.setData(GL_ARRAY_BUFFER, this->vertexes, count * sizeof(*this->vertexes) * 2, GL_FLOAT, 2, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::updateIndices()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			GLuint currentIndice = i * 4;
			this->indices[count++] = currentIndice + 0;
			this->indices[count++] = currentIndice + 2;
			this->indices[count++] = currentIndice + 1;
			this->indices[count++] = currentIndice + 3;
			this->indices[count++] = currentIndice + 1;
			this->indices[count++] = currentIndice + 2;
		}
		this->indicesBuffer.setData(GL_ELEMENT_ARRAY_BUFFER, this->indices, count * sizeof(this->indices), GL_UNSIGNED_INT, 1, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::updateColors()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderSpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_SPRITE_UPDATE_COLORS)
			{
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * 4 * sizeof(*this->colors));
				entry->removeChange(SHADER_SPRITE_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber() * 4;
		}
		this->colorsBuffer.setData(GL_ARRAY_BUFFER, this->colors, count * sizeof(*this->colors) * 4, GL_FLOAT, 4, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::resize()
	{
		updateVerticesNumber();
		if (!this->verticesNumber)
			return;
		delete[] (this->texCoords);
		this->texCoords = new float[this->verticesNumber * 2];
		delete[] (this->vertexes);
		this->vertexes = new float[this->verticesNumber * 2];
		delete[] (this->colors);
		this->colors = new float[this->verticesNumber * 4];
		delete[] (this->indices);
		this->indices = new GLuint[this->verticesNumber * 6 / 4];
	}

	void ShaderSpriteBatch::draw(glm::mat4 &viewProj)
	{
		if (!this->texture || !this->program || !this->texCoordsLocation || !this->vertexesLocation || !this->colorsLocation || !this->mvpLocation)
			return;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->update();
		if (this->mustResize)
			resize();
		if (!this->verticesNumber)
			return;
		if (this->mustResize)
			this->changes = SHADER_SPRITE_UPDATE_TEX_COORDS | SHADER_SPRITE_UPDATE_VERTEXES | SHADER_SPRITE_UPDATE_COLORS;
		if (this->mustResize)
			updateIndices();
		if (this->changes & SHADER_SPRITE_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & SHADER_SPRITE_UPDATE_VERTEXES)
			updateVertexes();
		if (this->changes & SHADER_SPRITE_UPDATE_COLORS)
			updateColors();
		if (this->mustResize)
			this->mustResize = false;
		this->changes = 0;
		this->texture->bind();
		this->program->use();
		this->texCoordsLocation->setVertexBuffer(this->texCoordsBuffer);
		this->vertexesLocation->setVertexBuffer(this->vertexesBuffer);
		this->colorsLocation->setVertexBuffer(this->colorsBuffer);
		this->indicesBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(this->x, this->y, 0));
		glm::mat4 mvp = viewProj * model;
		this->mvpLocation->setMat4f(mvp);
		glDrawElements(GL_TRIANGLES, this->verticesNumber * 6 / 4, GL_UNSIGNED_INT, NULL);
	}

	void ShaderSpriteBatch::addEntry(ShaderSpriteBatchEntry *entry)
	{
		entry->setParent(this);
		this->entries.push_back(entry);
	}

	void ShaderSpriteBatch::removeEntry(ShaderSpriteBatchEntry *entry)
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

	void ShaderSpriteBatch::setTexture(Texture *texture)
	{
		this->texture = texture;
		this->changes = SHADER_SPRITE_UPDATE_TEX_COORDS | SHADER_SPRITE_UPDATE_VERTEXES | SHADER_SPRITE_UPDATE_COLORS;
	}

}
