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
		Texture *texture;
		Vec2 *texCoords;
		Vec2 *vertexes;
		Vec4 *colors;
		Vec2 pos;
		uint32_t verticesNumber;
		uint8_t changes;
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
		inline std::vector<SpriteBatchEntry*> &getEntries() {return (this->entries);};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void setX(float x) {this->pos.x = x;};
		inline void setY(float y) {this->pos.y = y;};
		inline void setMustResize(bool mustResize) {this->mustResize = mustResize;};

	};

}

#endif
