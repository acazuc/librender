#ifndef LIBRENDER_SPRITE_BATCH_H
# define LIBRENDER_SPRITE_BATCH_H

# include "./SpriteBatchEntry.h"
# include <vector>

namespace librender
{

	class SpriteBatch
	{

	private:
		std::vector<SpriteBatchEntry*> entries;
		GLfloat *texCoords;
		GLfloat *vertex;
		GLfloat *colors;
		Texture *texture;
		uint32_t verticesNumber;
		uint8_t changes;
		float x;
		float y;
		bool mustResize;
		void updateVerticesNumber();
		void updateTexCoords();
		void updateVertex();
		void updateColors();
		void resize();

	public:
		SpriteBatch();
		~SpriteBatch();
		void draw();
		void addEntry(SpriteBatchEntry *entry);
		void removeEntry(SpriteBatchEntry *entry);
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return (this->texture);};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void setX(float x) {this->x = x;};
		inline void setY(float y) {this->y = y;};
		inline void setMustResize(bool mustResize) {this->mustResize = mustResize;};

	};

}

#endif
