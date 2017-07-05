#include "Text.h"

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
		//glGenBuffers(3, buffers);
	}

	Text::~Text()
	{
		//glDeleteBuffers(3, buffers);
	}

	/*void Text::updateVertex()
	{
		TextEntry::updateVertex();
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * 2 * sizeof(*this->vertex), this->vertex, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Text::updateTexCoords()
	{
		TextEntry::updateTexCoords();
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[TEX_CORRDS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * 2 * sizeof(*this->texCoords), this->texCoords, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Text::updateColors()
	{
		TextEntry::updateColors();
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[TEX_CORRDS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * 4 * sizeof(*this->colors), this->colors, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}*/

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
