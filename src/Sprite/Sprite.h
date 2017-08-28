#ifndef LIBRENDER_SPRITE_H
# define LIBRENDER_SPRITE_H

# include "./SpriteEntry.h"
# include "../Texture.h"

namespace librender
{

	class Sprite : public SpriteEntry
	{

	protected:
		Texture *texture;

	public:
		Sprite();
		~Sprite();
		void draw();
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return (this->texture);};

	};

}

#endif
