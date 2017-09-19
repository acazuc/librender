#include "Sprite.h"
#include "./SpriteUpdate.h"
#include "../GL.h"

namespace librender
{

	Sprite::Sprite()
	: SpriteEntry()
	, texture(NULL)
	{
		//Empty
	}

	Sprite::~Sprite()
	{
		//Empty
	}

	void Sprite::draw()
	{
		if (!this->texture)
			return;
		update();
		this->texture->bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors);
		glVertexPointer(2, GL_FLOAT, 0, this->vertex);
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords);
		glPushMatrix();
		glTranslatef(this->x, this->y, 0);
		glDrawArrays(GL_QUADS, 0, this->verticesNumber);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void Sprite::setTexture(Texture *texture)
	{
		if (this->texture == texture)
			return;
		this->texture = texture;
		this->updatesRequired |= SPRITE_UPDATE_VERTEXES;
		this->updatesRequired |= SPRITE_UPDATE_TEX_COORDS;
	}

}
