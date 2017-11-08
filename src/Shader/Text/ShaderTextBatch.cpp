#include "ShaderTextBatch.h"
#include "./ShaderTextUpdate.h"
#include "../../GL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

namespace librender
{

	ShaderTextBatch::ShaderTextBatch()
	: texCoordsLocation(NULL)
	, vertexesLocation(NULL)
	, colorsLocation(NULL)
	, mvpLocation(NULL)
	, program(NULL)
	, font(NULL)
	, texCoords(NULL)
	, vertexes(NULL)
	, colors(NULL)
	, verticesNumber(0)
	, changes(0)
	, x(0)
	, y(0)
	, mustResize(true)
	{
		//Empty
	}

	ShaderTextBatch::~ShaderTextBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
		delete[] (this->texCoords);
		delete[] (this->vertexes);
		delete[] (this->colors);
	}

	void ShaderTextBatch::updateVerticesNumber()
	{
		this->verticesNumber = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->verticesNumber += this->entries[i]->getVerticesNumber();
	}

	void ShaderTextBatch::updateTexCoords()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderTextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_TEXT_UPDATE_TEX_COORDS)
			{
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * 2 * sizeof(*this->texCoords));
				entry->removeChanges(SHADER_TEXT_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber() * 2;
		}
		this->texCoordsBuffer.setData(GL_ARRAY_BUFFER, this->texCoords, count * sizeof(*this->texCoords), GL_FLOAT, 2, GL_DYNAMIC_DRAW);
	}

	void ShaderTextBatch::updateVertexes()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderTextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_TEXT_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertexes(), entry->getVerticesNumber() * 2 * sizeof(*this->vertexes));
				entry->removeChanges(SHADER_TEXT_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber() * 2;
		}
		this->vertexesBuffer.setData(GL_ARRAY_BUFFER, this->vertexes, count * sizeof(*this->vertexes), GL_FLOAT, 2, GL_DYNAMIC_DRAW);
	}

	void ShaderTextBatch::updateIndices()
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

	void ShaderTextBatch::updateColors()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderTextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_TEXT_UPDATE_COLORS)
			{
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * 4 * sizeof(*this->colors));
				entry->removeChanges(SHADER_TEXT_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber() * 4;
		}
		this->colorsBuffer.setData(GL_ARRAY_BUFFER, this->colors, count * sizeof(*this->colors), GL_FLOAT, 4, GL_DYNAMIC_DRAW);
	}

	void ShaderTextBatch::resize()
	{
		updateVerticesNumber();
		if (!this->verticesNumber)
			return;
		delete[] (this->texCoords);
		this->texCoords = new GLfloat[this->verticesNumber * 2];
		delete[] (this->vertexes);
		this->vertexes = new GLfloat[this->verticesNumber * 2];
		delete[] (this->colors);
		this->colors = new GLfloat[this->verticesNumber * 4];
	}

	void ShaderTextBatch::draw(glm::mat4 &viewProj)
	{
		if (!this->font || !this->program || !this->texCoordsLocation || !this->vertexesLocation || !this->colorsLocation || !this->mvpLocation)
			return;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->update();
		if (this->mustResize)
			resize();
		if (!this->verticesNumber)
			return;
		if (this->mustResize)
		{
			this->changes = SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES | SHADER_TEXT_UPDATE_COLORS;
			updateIndices();
		}
		if (this->changes & SHADER_TEXT_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->changes & SHADER_TEXT_UPDATE_VERTEXES)
			updateVertexes();
		if (this->changes & SHADER_TEXT_UPDATE_COLORS)
			updateColors();
		if (this->mustResize)
			this->mustResize = false;
		this->changes = 0;
		this->font->bind();
		this->program->use();
		this->texCoordsLocation->setVertexBuffer(this->texCoordsBuffer);
		this->vertexesLocation->setVertexBuffer(this->vertexesBuffer);
		this->colorsLocation->setVertexBuffer(this->colorsBuffer);
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(this->x, this->y, 0));
		glm::mat4 mvp = viewProj * model;
		this->mvpLocation->setMat4f(mvp);
		glDrawElements(GL_TRIANGLES, this->verticesNumber / 4 * 6, GL_UNSIGNED_INT, NULL);
	}

	void ShaderTextBatch::addEntry(ShaderTextBatchEntry *entry)
	{
		entry->setParent(this);
		this->entries.push_back(entry);
		this->mustResize = true;
		this->changes = SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES | SHADER_TEXT_UPDATE_COLORS;
	}

	void ShaderTextBatch::removeEntry(ShaderTextBatchEntry *entry)
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			if (this->entries[i] == entry)
			{
				this->entries.erase(this->entries.begin() + i);
				entry->setParent(NULL);
				this->mustResize = true;
				this->changes = SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES | SHADER_TEXT_UPDATE_COLORS;
				return;
			}
		}
	}

	void ShaderTextBatch::clearEntries()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(NULL);
		this->entries.clear();
		this->mustResize = true;
		this->changes = SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES | SHADER_TEXT_UPDATE_COLORS;
	}

	void ShaderTextBatch::setFont(Font *font)
	{
		this->font = font;
		this->changes = SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderTextBatchEntry *entry = this->entries[i];
			entry->addChanges(SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES);
			entry->recalcWidth();
			entry->recalcHeight();
		}
	}

}
