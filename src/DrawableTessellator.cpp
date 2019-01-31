#include "DrawableTessellator.h"
#include "./DrawableBuffers.h"

namespace librender
{

	DrawableTessellator::DrawableTessellator(Context *context)
	: Drawable(context)
	{
	}

	void DrawableTessellator::addPoint(Vec2 vertex, Vec2 texCoords, Vec4 color)
	{
		this->texCoords.push_back(texCoords);
		this->vertexes.push_back(vertex);
		this->colors.push_back(color);
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS);
	}

	void DrawableTessellator::addIndice(uint32_t indice)
	{
		this->indices.push_back(indice);
		requireUpdates(DRAWABLE_BUFFER_INDICES);
	}

	void DrawableTessellator::clear()
	{
		std::vector<uint32_t> emptyIndices;
		std::vector<Vec2> emptyTexCoords;
		std::vector<Vec2> emptyVertexes;
		std::vector<Vec4> emptyColors;
		this->texCoords.swap(emptyTexCoords);
		this->vertexes.swap(emptyVertexes);
		this->indices.swap(emptyIndices);
		this->colors.swap(emptyColors);
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS);
		requireUpdates(DRAWABLE_BUFFER_INDICES);
	}

}
