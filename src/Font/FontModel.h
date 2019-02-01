#ifndef LIBRENDER_FONT_MODEL_H
# define LIBRENDER_FONT_MODEL_H

# include "../Context/Context.h"
# include <ft2build.h>
# include FT_FREETYPE_H
# include <string>

namespace librender
{

	class Font;

	class FontModel
	{

	private:
		static FT_Library ftLib;
		Context &context;
		FT_Face ftFace;
		void _load();

	public:
		FontModel(Context &context, std::string filename);
		FontModel(Context &context, char *data, size_t len);
		~FontModel();
		Font *derive(uint32_t size);
		bool setSize(uint32_t size);
		inline Context &getContext() {return this->context;};
		inline FT_Face &getFtFace() {return this->ftFace;};

	};

}

#endif
