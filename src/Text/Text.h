#ifndef LIBRENDER_TEXT_H
# define LIBRENDER_TEXT_H

# include "../Font/Font.h"
# include "./TextBase.h"

namespace librender
{

	class Text : public TextBase
	{

	protected:
		Font *font;
		uint32_t lastVerticesNumber;
		void resize(uint32_t len);

	public:
		Text();
		void draw();
		void setFont(Font *font);
		inline Font *getFont() {return this->font;};

	};

}

#endif
