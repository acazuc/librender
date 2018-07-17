#ifndef LIBRENDER_SPRITE_BATCH_ENTRY_H
# define LIBRENDER_SPRITE_BATCH_ENTRY_H

# include "./SpriteEntry.h"

namespace librender
{

	class SpriteBatch;

	class SpriteBatchEntry : public SpriteEntry
	{

	private:
		SpriteBatch *parent;
		uint8_t changes;

	public:
		SpriteBatchEntry();
		~SpriteBatchEntry();
		void update();
		Texture *getTexture();
		void setParent(SpriteBatch *spriteBatch);
		void setX(float x);
		float getX();
		void setY(float y);
		float getY();
		void setWidth(float width);
		void setHeight(float height);
		inline uint8_t getChanges() {return this->changes;};
		inline void removeChange(uint8_t change) {this->changes &= ~change;};

	};

}

#endif
