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
		GLfloat *texCoords;
		GLfloat *vertex;
		GLfloat *colors;
		Font *font;
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
		TextBatch();
		~TextBatch();
		void draw();
		void addEntry(TextBatchEntry *entry);
		void removeEntry(TextBatchEntry *entry);
		void clearEntries();
		void setFont(Font *font);
		inline Font *getFont() {return (this->font);};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void setX(float x) {this->x = x;};
		inline void setY(float y) {this->y = y;};
		inline void setMustResize(bool mustResize) {this->mustResize = mustResize;};

	};

}

#endif
