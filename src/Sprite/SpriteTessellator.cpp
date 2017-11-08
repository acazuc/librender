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
		std::vector<glm::vec2> emptyTexCoords;
		std::vector<glm::vec2> emptyVertexes;
		std::vector<glm::vec4> emptyColors;
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

	void SpriteTessellator::add(glm::vec2 vertex, glm::vec2 texCoords, glm::vec4 color)
	{
		this->texCoords.push_back(texCoords);
		this->vertexes.push_back(vertex);
		this->colors.push_back(color);
	}

}
