#include "Text.h"
#include "./TextUpdate.h"
#include "../GL.h"

namespace librender
{

	Text::Text()
	: TextEntry()
	, font(NULL)
	{
		//Empty
	}

	Text::~Text()
	{
		//Empty
	}

	void Text::draw()
	{
		if (!this->font)
			return;
		update();
		this->font->bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, this->colors);
		glVertexPointer(2, GL_FLOAT, 0, this->vertexes);
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords);
		glPushMatrix();
		glTranslatef(this->x, this->y, 0);
		glScalef(this->scaleX, this->scaleY, 0);
		glDrawArrays(GL_QUADS, 0, this->verticesNumber);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void Text::setFont(Font *font)
	{
		if (this->font == font)
			return;
		this->font = font;
		this->lineHeight = this->font->getLineHeight();
		this->updatesRequired |= TEXT_UPDATE_VERTEXES;
		this->updatesRequired |= TEXT_UPDATE_TEX_COORDS;
		recalcWidth();
		recalcHeight();
	}

}
