#ifndef LIBRENDER_SPRITE_H
# define LIBRENDER_SPRITE_H

# include "./SpriteBase.h"

namespace librender
{

	class Sprite : public SpriteBase
	{

	protected:
		Texture *texture;

	public:
		Sprite();
		void draw();
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return this->texture;};

	};

}

#endif
