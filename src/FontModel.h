#ifndef LIBRENDER_FONT_MODEL_H
# define LIBRENDER_FONT_MODEL_H

# include <string>
# include <ft2build.h>
# include FT_FREETYPE_H

# define LIBRENDER_FONT_MODEL_CHARS_NUMBER 1300

namespace librender
{

	class Font;

	class FontModel
	{

	private:
		static FT_Library ftLib;
		FT_Face ftFace;
		bool availableChars[LIBRENDER_FONT_MODEL_CHARS_NUMBER];
		void _load();

	public:
		FontModel(std::string filename);
		FontModel(char *ttfData, size_t ttfLen);
		~FontModel();
		Font *derive(int size);
		bool isAvailable(unsigned int c) {return (this->availableChars[c]);};

	};

}

#endif
