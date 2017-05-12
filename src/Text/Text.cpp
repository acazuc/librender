#include "Text.h"
#include <cstring>
#include <utf8.h>

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
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * 2 * sizeof(*this->vertex), this->vertex, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Text::updateTexCoords()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[TEX_CORRDS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * 2 * sizeof(*this->texCoords), this->texCoords, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Text::updateColors()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[TEX_CORRDS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * 4 * sizeof(*this->colors), this->colors, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}*/

	void Text::draw()
	{
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
		/*glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[VERTEX_BUFFER]);
		glVertexAttribPointer(
		   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   this->verticesNumber,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   0,                  // stride
		   (void*)0            // array buffer offset
	   );*/
		glDrawArrays(GL_QUADS, 0, this->verticesNumber);
		//glDisableVertexAttribArray(0);
		glPopMatrix();
	}

	void Text::setFont(Font *font)
	{
		if (font == this->font)
			return;
		this->font = font;
		this->lineHeight = this->font->getLineHeight();
		this->updatesRequired |= UPDATE_VERTEX;
		this->updatesRequired |= UPDATE_TEX_COORDS;
	}

}
