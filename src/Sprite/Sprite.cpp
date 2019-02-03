#include "Sprite.h"
#include "../DrawableBuffers.h"

namespace librender
{

	Sprite::Sprite(Context &context)
	: Drawable(context)
	, texture(nullptr)
	{
		requireUpdates(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_COLORS | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS);
	}

	void Sprite::draw()
	{
		this->context.setSamplerTexture(0, this->texture);
		updateBuffers();
		Drawable::draw();
	}

	void Sprite::setTexture(Texture *texture)
	{
		if (this->texture == texture)
			return;
		this->texture = texture;
		requireUpdates(DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_TEX_COORDS);
	}

}
