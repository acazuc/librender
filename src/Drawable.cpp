#include "Drawable.h"
#include "./DrawableBuffers.h"
#include "./GL.h"

namespace librender
{

	Drawable::Drawable()
	: scale(1)
	, pos(0)
	, verticesNumber(0)
	, indicesNumber(0)
	, shapeType(GL_TRIANGLES)
	, updatesRequired(0)
	, buffers(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS | DRAWABLE_BUFFER_TEX_COORDS)
	{
	}

	void Drawable::draw()
	{
		if (this->buffers & DRAWABLE_BUFFER_VERTEXES)
		{
			glVertexPointer(2, GL_FLOAT, 0, this->vertexes.data());
			glEnableClientState(GL_VERTEX_ARRAY);
		}
		else
		{
			glDisableClientState(GL_VERTEX_ARRAY);
		}
		if (this->buffers & DRAWABLE_BUFFER_COLORS)
		{
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, 0, this->colors.data());
		}
		else
		{
			glDisableClientState(GL_COLOR_ARRAY);
		}
		if (this->buffers & DRAWABLE_BUFFER_TEX_COORDS)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords.data());
		}
		else
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		glPushMatrix();
		glTranslatef(this->pos.x, this->pos.y, 0);
		glScalef(this->scale.x, this->scale.y, 0);
		glDrawElements(this->shapeType, this->indices.size(), GL_UNSIGNED_INT, this->indices.data());
		glPopMatrix();
	}

	void Drawable::requireUpdates(uint8_t update)
	{
		this->updatesRequired |= update;
	}

}
