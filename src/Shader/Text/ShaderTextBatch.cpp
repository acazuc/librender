#include "ShaderTextBatch.h"
#include "./ShaderTextUpdate.h"
#include "../../GL.h"
#include <cstring>

namespace librender
{

	ShaderTextBatch::ShaderTextBatch()
	: texCoords(nullptr)
	, vertexes(nullptr)
	, colors(nullptr)
	, font(nullptr)
	, pos(0)
	, verticesNumber(0)
	, changes(0)
	, mustResize(true)
	{
		//Empty
	}

	ShaderTextBatch::~ShaderTextBatch()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(nullptr);
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
				std::memcpy(&this->texCoords[count], entry->getTexCoords(), entry->getVerticesNumber() * sizeof(*this->texCoords));
				entry->removeChanges(SHADER_TEXT_UPDATE_TEX_COORDS);
			}
			count += entry->getVerticesNumber();
		}
		this->texCoordsBuffer.setData(GL_ARRAY_BUFFER, this->texCoords, count * sizeof(*this->texCoords), GL_DYNAMIC_DRAW);
	}

	void ShaderTextBatch::updateVertexes()
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < this->entries.size(); ++i)
		{
			ShaderTextBatchEntry *entry = this->entries[i];
			if (this->mustResize || entry->getChanges() & SHADER_TEXT_UPDATE_VERTEXES)
			{
				std::memcpy(&this->vertexes[count], entry->getVertexes(), entry->getVerticesNumber() * sizeof(*this->vertexes));
				entry->removeChanges(SHADER_TEXT_UPDATE_VERTEXES);
			}
			count += entry->getVerticesNumber();
		}
		this->vertexesBuffer.setData(GL_ARRAY_BUFFER, this->vertexes, count * sizeof(*this->vertexes), GL_DYNAMIC_DRAW);
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
		this->indicesBuffer.setData(GL_ELEMENT_ARRAY_BUFFER, indices, count * sizeof(*indices), GL_DYNAMIC_DRAW);
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
				std::memcpy(&this->colors[count], entry->getColors(), entry->getVerticesNumber() * sizeof(*this->colors));
				entry->removeChanges(SHADER_TEXT_UPDATE_COLORS);
			}
			count += entry->getVerticesNumber();
		}
		this->colorsBuffer.setData(GL_ARRAY_BUFFER, this->colors, count * sizeof(*this->colors), GL_DYNAMIC_DRAW);
	}

	void ShaderTextBatch::resize()
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

	void ShaderTextBatch::draw(Mat4 &viewProj)
	{
		if (!this->font || !this->program.program || !this->program.texCoordsLocation || !this->program.vertexesLocation || !this->program.colorsLocation || !this->program.mvpLocation)
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
		this->program.program->use();
		this->program.texCoordsLocation->setVertexBuffer(this->texCoordsBuffer, 2, GL_FLOAT);
		this->program.vertexesLocation->setVertexBuffer(this->vertexesBuffer, 2, GL_FLOAT);
		this->program.colorsLocation->setVertexBuffer(this->colorsBuffer, 4, GL_FLOAT);
		Mat4 model(Mat4::translate(Mat4(1), Vec3(this->pos, 0)));
		Mat4 mvp(viewProj * model);
		this->program.mvpLocation->setMat4f(mvp);
		glDrawElements(GL_TRIANGLES, this->verticesNumber / 4 * 6, GL_UNSIGNED_INT, nullptr);
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
				entry->setParent(nullptr);
				this->mustResize = true;
				this->changes = SHADER_TEXT_UPDATE_TEX_COORDS | SHADER_TEXT_UPDATE_VERTEXES | SHADER_TEXT_UPDATE_COLORS;
				return;
			}
		}
	}

	void ShaderTextBatch::clearEntries()
	{
		for (uint32_t i = 0; i < this->entries.size(); ++i)
			this->entries[i]->setParent(nullptr);
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

	int32_t ShaderTextBatch::getLineHeight()
	{
		if (!this->font)
			return 0;
		return this->font->getLineHeight();
	}

}
