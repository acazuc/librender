#ifndef LIBRENDER_TEXT_BATCH_H
# define LIBRENDER_TEXT_BATCH_H

# include "TextBatchEntry.h"
# include <vector>

namespace librender
{

	class TextBatchEntry;

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
		void updateVerticesNumber();
		void updateTexCoords();
		void updateVertex();
		void updateColors();

	public:
		TextBatch();
		~TextBatch();
		void draw();
		void addEntry(TextBatchEntry *entry);
		void removeEntry(TextBatchEntry *entry);
		void setFont(Font *font);
		inline Font *getFont() {return (this->font);};
		void addChanges(uint8_t changes) {this->changes |= changes;};
		void setX(float x) {this->x = x;};
		void setY(float y) {this->y = y;};

	};

}

#endif
