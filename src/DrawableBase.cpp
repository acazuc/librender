#include "DrawableBase.h"
#include "./DrawableBuffers.h"

namespace librender
{

	void DrawableBase::resize(uint32_t vertices, uint32_t indices)
	{
		if (this->verticesNumber != vertices)
		{
			this->verticesNumber = vertices;
			this->texCoords.resize(this->verticesNumber);
			this->vertexes.resize(this->verticesNumber);
			this->colors.resize(this->verticesNumber);
			requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_COLORS);
		}
		if (this->indicesNumber != indices)
		{
			this->indicesNumber = indices;
			this->indices.resize(this->indicesNumber);
			requireUpdates(DRAWABLE_BUFFER_INDICES);
		}
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
