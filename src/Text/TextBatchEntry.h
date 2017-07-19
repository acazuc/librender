#ifndef LIBRENDER_TEXT_BATCH_ENTRY_H
# define LIBRENDER_TEXT_BATCH_ENTRY_H

# include "./TextEntry.h"

namespace librender
{

	class TextBatch;

	class TextBatchEntry : public TextEntry
	{

	private:
		TextBatch *parent;
		uint8_t changes;
		void resize(uint32_t len);

	public:
		TextBatchEntry();
		~TextBatchEntry();
		void update();
		Font *getFont();
		void setParent(TextBatch *textBatch);
		void setX(float x);
		void setY(float y);
		inline uint8_t getChanges() {return (this->changes);};
		inline void removeChanges(uint8_t changes) {this->changes &= ~changes;};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};

	};

}

#endif
