#ifndef LIBRENDER_TEXT_BATCH_H
# define LIBRENDER_TEXT_BATCH_H

# include "./TextBatchEntry.h"
# include <vector>

namespace librender
{

	class TextBatch
	{

	private:
		std::vector<TextBatchEntry*> entries;
		std::vector<uint32_t> indices;
		std::vector<Vec2> texCoords;
		std::vector<Vec2> vertexes;
		std::vector<Vec4> colors;
		Font *font;
		Vec2 pos;
		uint32_t verticesNumber;
		uint8_t changes;
		bool mustResize;
		void updateVerticesNumber();
		void updateTexCoords();
		void updateVertexes();
		void updateIndices();
		void updateColors();
		void resize();

	public:
		TextBatch();
		~TextBatch();
		void draw();
		void addEntry(TextBatchEntry *entry);
		void removeEntry(TextBatchEntry *entry);
		void clearEntries();
		int32_t getLineHeight();
		void setFont(Font *font);
		inline Font *getFont() {return this->font;};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void setX(float x) {this->pos.x = x;};
		inline void setY(float y) {this->pos.y = y;};
		inline void setMustResize(bool mustResize) {this->mustResize = mustResize;};

	};

}

#endif
