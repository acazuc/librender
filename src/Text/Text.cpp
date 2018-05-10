#include "Text.h"
#include "./TextUpdate.h"
#include "../GL.h"

namespace librender
{

	Text::Text()
	: font(nullptr)
	, mustResize(false)
	{
		//Empty
	}

	Text::~Text()
	{
		//Empty
	}

	void Text::updateIndices()
	{
		uint32_t count = 0;
		GLuint currentIndice = 0;
		for (uint32_t i = 0; i < this->verticesNumber / 4; ++i)
		{
			indices[count++] = currentIndice + 0;
			indices[count++] = currentIndice + 3;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 2;
			indices[count++] = currentIndice + 1;
			indices[count++] = currentIndice + 3;
			currentIndice += 4;
		}
	}

	void Text::resize(uint32_t len)
	{
		this->mustResize = true;
		TextEntry::resize(len);
	}

	void Text::draw()
	{
		if (!this->font)
			return;
		update();
		if (this->mustResize)
		{
			this->mustResize = false;
			this->indices.resize(this->verticesNumber / 4 * 6);
			updateIndices();
		}
		this->font->bind();
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
