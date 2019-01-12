#include "DrawableTessellator.h"

namespace librender
{

	void DrawableTessellator::addPoint(Vec2 vertex, Vec2 texCoords, Vec4 color)
	{
		this->texCoords.push_back(texCoords);
		this->vertexes.push_back(vertex);
		this->colors.push_back(color);
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
	}

}
