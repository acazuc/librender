#ifndef LIBRENDER_TEXT_H
# define LIBRENDER_TEXT_H

# include "../Font/Font.h"
# include "./TextEntry.h"

namespace librender
{

	class Text : public TextEntry
	{

	protected:
		Font *font;

	public:
		Text();
		~Text();
		void draw();
		void setFont(Font *font);
		inline Font *getFont() {return (this->font);};

	};

}

#endif
