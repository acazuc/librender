#include "Text.h"
#include "GL.h"

#define UPDATE_VERTEX 1
#define UPDATE_TEX_COORDS 2
#define UPDATE_COLORS 4

#define VERTEX_BUFFER 0
#define TEX_COORD_BUFFER 1
#define COLOR_BUFFER 2

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
		glVertexPointer(2, GL_FLOAT, 0, this->vertex);
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
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

}
