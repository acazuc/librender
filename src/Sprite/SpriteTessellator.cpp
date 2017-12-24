#include "SpriteTessellator.h"

namespace librender
{

	SpriteTessellator::SpriteTessellator()
	: texture(NULL)
	{
		//Empty
	}

	void SpriteTessellator::clear()
	{
		std::vector<Vec2> emptyTexCoords;
		std::vector<Vec2> emptyVertexes;
		std::vector<Vec4> emptyColors;
		this->texCoords.swap(emptyTexCoords);
		this->vertexes.swap(emptyVertexes);
		this->colors.swap(emptyColors);
	}

	void SpriteTessellator::draw()
	{
		if (!this->texture)
			return;
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors.data());
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes.data());
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords.data());
		glDrawArrays(GL_QUADS, 0, this->texCoords.size());
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void SpriteTessellator::add(Vec2 vertex, Vec2 texCoords, Vec4 color)
	{
		this->texCoords.push_back(texCoords);
		this->vertexes.push_back(vertex);
		this->colors.push_back(color);
	}

}
