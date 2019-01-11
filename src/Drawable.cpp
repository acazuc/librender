#include "Drawable.h"
#include "./GL.h"

namespace librender
{

	Drawable::Drawable()
	: scale(1)
	, pos(0)
	, verticesNumber(0)
	, indicesNumber(0)
	, updatesRequired(0)
	{
	}

	void Drawable::draw()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors.data());
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes.data());
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords.data());
		glPushMatrix();
		glTranslatef(this->pos.x, this->pos.y, 0);
		glScalef(this->scale.x, this->scale.y, 0);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, this->indices.data());
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void Drawable::requireUpdates(uint8_t update)
	{
		this->updatesRequired |= update;
	}

}
