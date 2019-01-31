#include "DrawableBase.h"
#include "./DrawableBuffers.h"

namespace librender
{

	DrawableBase::DrawableBase()
	: scale(1)
	, pos(0)
	, verticesNumber(0)
	, indicesNumber(0)
	, updatesRequired(0)
	, buffers(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS | DRAWABLE_BUFFER_TEX_COORDS)
	{
	}

	void DrawableBase::fillIndices(std::vector<uint32_t>::iterator indices)
	{
		(void)indices;
	}

	void DrawableBase::fillTexCoords(std::vector<Vec2>::iterator texCoords)
	{
		(void)texCoords;
	}

	void DrawableBase::fillVertexes(std::vector<Vec2>::iterator vertexes)
	{
		(void)vertexes;
	}

	void DrawableBase::fillColors(std::vector<Vec4>::iterator colors)
	{
		(void)colors;
	}

	void DrawableBase::setVerticesNumber(uint32_t verticesNumber)
	{
		this->verticesNumber = verticesNumber;
	}

	void DrawableBase::setIndicesNumber(uint32_t indicesNumber)
	{
		this->indicesNumber = indicesNumber;
	}

	void DrawableBase::requireUpdates(uint8_t update)
	{
		this->updatesRequired |= this->buffers & update;
	}

	void DrawableBase::updateBuffers()
	{
		if (this->updatesRequired & DRAWABLE_BUFFER_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & DRAWABLE_BUFFER_VERTEXES)
			updateVertexes();
		if (this->updatesRequired & DRAWABLE_BUFFER_INDICES)
			updateIndices();
		if (this->updatesRequired & DRAWABLE_BUFFER_COLORS)
			updateColors();
		this->updatesRequired = 0;
	}

}
