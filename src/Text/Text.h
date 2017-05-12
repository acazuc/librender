#ifndef LIBRENDER_TEXT_H
# define LIBRENDER_TEXT_H

# include "../Font/Font.h"
# include "TextEntry.h"
# include "../Color.h"
# include "../GL.h"
# include <cstdint>
# include <string>

namespace librender
{

	class Text : public TextEntry
	{

	protected:
		GLuint buffers[3];
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
