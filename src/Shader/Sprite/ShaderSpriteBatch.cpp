#include "ShaderSpriteBatch.h"
#include "./ShaderSpriteUpdate.h"
#include "../../GL.h"
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

	ShaderSpriteBatch::~ShaderSpriteBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
		delete[] (this->texCoords);
		delete[] (this->vertexes);
		delete[] (this->colors);
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
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * sizeof(*this->texCoords));
				entry->removeChange(SHADER_SPRITE_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber();
		}
		this->texCoordsBuffer.setData(GL_ARRAY_BUFFER, this->texCoords, count * sizeof(*this->texCoords), GL_FLOAT, 2, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::updateVertexes()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderSpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_SPRITE_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertexes(), entry->getVerticesNumber() * sizeof(*this->vertexes));
				entry->removeChange(SHADER_SPRITE_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber();
		}
		this->vertexesBuffer.setData(GL_ARRAY_BUFFER, this->vertexes, count * sizeof(*this->vertexes), GL_FLOAT, 2, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::updateIndices()
	{
		GLuint *indices = new GLuint[this->verticesNumber / 4 * 6];
		uint32_t count = 0;
		GLuint currentIndice = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			indices[count++] = currentIndice + 0;
			indices[count++] = currentIndice + 3;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 2;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 3;
			currentIndice += this->entries[i]->getVerticesNumber();
		}
		this->indicesBuffer.setData(GL_ELEMENT_ARRAY_BUFFER, indices, count * sizeof(*indices), GL_UNSIGNED_INT, 1, GL_DYNAMIC_DRAW);
		delete[] (indices);
	}

	void ShaderSpriteBatch::updateColors()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderSpriteBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_SPRITE_UPDATE_COLORS)
			{
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * sizeof(*this->colors));
				entry->removeChange(SHADER_SPRITE_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber();
		}
		this->colorsBuffer.setData(GL_ARRAY_BUFFER, this->colors, count * sizeof(*this->colors), GL_FLOAT, 4, GL_DYNAMIC_DRAW);
	}

	void ShaderSpriteBatch::resize()
	{
		updateVerticesNumber();
		if (!this->verticesNumber)
			return;
		delete[] (this->texCoords);
		this->texCoords = new Vec2[this->verticesNumber];
		delete[] (this->vertexes);
		this->vertexes = new Vec2[this->verticesNumber];
		delete[] (this->colors);
		this->colors = new Vec4[this->verticesNumber];
	}

	void ShaderSpriteBatch::draw(Mat4 &viewProj)
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
		{
			this->changes = SHADER_SPRITE_UPDATE_TEX_COORDS | SHADER_SPRITE_UPDATE_VERTEXES | SHADER_SPRITE_UPDATE_COLORS;
			updateIndices();
		}
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
		Mat4 model(Mat4::translate(Mat4(1), Vec3(this->pos, 0)));
		Mat4 mvp(viewProj * model);
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
