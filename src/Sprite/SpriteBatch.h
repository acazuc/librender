#ifndef LIBRENDER_SPRITE_BATCH_H
# define LIBRENDER_SPRITE_BATCH_H

# include "../DrawableBatch.h"

namespace librender
{

	class SpriteBatch : public DrawableBatch
	{

	private:
		Texture *texture;

	public:
		SpriteBatch(Context &context);
		void draw();
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return this->texture;};

	};

}

#endif
