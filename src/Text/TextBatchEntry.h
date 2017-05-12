#ifndef LIBRENDER_TEXT_BATCH_ENTRY_H
# define LIBRENDER_TEXT_BATCH_ENTRY_H

# include "TextEntry.h"

namespace librender
{

	class TextBatch;

	class TextBatchEntry : public TextEntry
	{

	private:
		TextBatch *parent;

	public:
		TextBatchEntry();
		~TextBatchEntry();
		void update();
		Font *getFont();
		void setParent(TextBatch *textBatch);
		void setX(float x);
		void setY(float y);

	};

}

#endif
