#include "Sprite.h"
#include "../DrawableUpdate.h"
#include "../GL.h"

namespace librender
{

	Sprite::Sprite()
	: texture(nullptr)
	{
	}

	void Sprite::draw()
	{
		if (this->texture)
			this->texture->bind();
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		updateBuffers();
		Drawable::draw();
	}

	void Sprite::setTexture(Texture *texture)
	{
		if (this->texture == texture)
			return;
		this->texture = texture;
		requireUpdates(DRAWABLE_UPDATE_VERTEXES | DRAWABLE_UPDATE_TEX_COORDS);
	}

}
