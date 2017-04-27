#ifndef LIBRENDER_TEXT_BATCH_H
# define LIBRENDER_TEXT_BATCH_H

namespace librender
{

	class TextBatch
	{

	private:
		std::vector<TextBatchEntry*> entries;
		Font *font;

	public:
		TextBatch();
		void draw();
		void addEntry(TextBatchEntry *entry);
		void removeEntry(TextBatchEntry *entry);
		void setFont(Font *font);

	};

}

#endif
