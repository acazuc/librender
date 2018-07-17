#ifndef LIBRENDER_TEXT_H
# define LIBRENDER_TEXT_H

# include "../Font/Font.h"
# include "./TextEntry.h"
# include <vector>

namespace librender
{

	class Text : public TextEntry
	{

	protected:
		std::vector<uint32_t> indices;
		Font *font;
		bool mustResize;
		void updateIndices();
		void resize(uint32_t len);

	public:
		Text();
		~Text();
		void draw();
		void setFont(Font *font);
		inline Font *getFont() {return this->font;};

	};

}

#endif
