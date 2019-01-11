#include "DrawableBase.h"
#include "./DrawableUpdate.h"

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
			requireUpdates(DRAWABLE_UPDATE_VERTEXES | DRAWABLE_UPDATE_TEX_COORDS | DRAWABLE_UPDATE_COLORS);
		}
		if (this->indicesNumber != indices)
		{
			this->indicesNumber = indices;
			this->indices.resize(this->indicesNumber);
			requireUpdates(DRAWABLE_UPDATE_INDICES);
		}
	}

	void DrawableBase::updateBuffers()
	{
		if (this->updatesRequired & DRAWABLE_UPDATE_TEX_COORDS)
			updateTexCoords();
		if (this->updatesRequired & DRAWABLE_UPDATE_VERTEXES)
			updateVertexes();
		if (this->updatesRequired & DRAWABLE_UPDATE_INDICES)
			updateIndices();
		if (this->updatesRequired & DRAWABLE_UPDATE_COLORS)
			updateColors();
		this->updatesRequired = 0;
	}

}
