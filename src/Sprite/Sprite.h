#ifndef LIBRENDER_SPRITE_H
# define LIBRENDER_SPRITE_H

# include "./SpriteBase.h"
# include "../Drawable.h"

namespace librender
{

	class Sprite : public SpriteBase, public Drawable
	{

	protected:
		Texture *texture;

	public:
		Sprite(Context &context);
		void draw();
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return this->texture;};

	};

}

#endif
