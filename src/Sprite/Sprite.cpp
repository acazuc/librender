#include "Sprite.h"
#include "./SpriteUpdate.h"
#include "../GL.h"

static uint32_t indices[6] = {0, 1, 2, 2, 3, 0};

namespace librender
{

	Sprite::Sprite()
	: SpriteEntry()
	, texture(nullptr)
	{
		//Empty
	}

	void Sprite::draw()
	{
		if (this->texture)
			this->texture->bind();
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		update();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors.data());
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes.data());
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords.data());
		glPushMatrix();
		glTranslatef(this->pos.x, this->pos.y, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
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
