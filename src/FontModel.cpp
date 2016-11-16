#include "FontModel.h"
#include "Font.h"

namespace librender
{

	FT_Library FontModel::ftLib = NULL;

	FontModel::FontModel(std::string filename)
	{
		if (FontModel::ftLib == NULL)
		{
			if (FT_Init_FreeType(&FontModel::ftLib))
				throw std::exception();
		}
		if (FT_New_Face(FontModel::ftLib, filename.c_str(), 0, &this->ftFace))
			throw std::exception();
		_load();
	}

	FontModel::FontModel(char *ttfData, size_t ttfLen)
	{
		if (FontModel::ftLib == NULL)
		{
			if (FT_Init_FreeType(&FontModel::ftLib))
				throw std::exception();
		}
		if (FT_New_Memory_Face(FontModel::ftLib, reinterpret_cast<FT_Byte*>(ttfData), ttfLen, 0, &this->ftFace))
			throw std::exception();
		_load();
	}

	FontModel::~FontModel()
	{
		if (FontModel::ftLib)
		{
			FT_Done_FreeType(FontModel::ftLib);
			FontModel::ftLib = NULL;
		}
	}

	void FontModel::_load()
	{
		if (FT_Select_Charmap(this->ftFace, ft_encoding_unicode))
			throw std::exception();
		if (FT_Set_Pixel_Sizes(this->ftFace, 0, 100))
			throw std::exception();
		for (uint32_t i = 0; i < UTILS_FONT_CHARS_NUMBER; ++i)
		{
			FT_UInt glyph;
			if (i <= 0x1F || i == 0x7F || (i >= 0x80 && i <= 0x9F) || !(glyph = FT_Get_Char_Index(this->ftFace, i)))
				this->availableChars[i] = false;
			else if (FT_Load_Glyph(this->ftFace, glyph, FT_LOAD_RENDER))
					this->availableChars[i] = false;
			else if (this->ftFace->glyph->advance.x == 0)
				this->availableChars[i] = false;
			else
				this->availableChars[i] = true;
		}
	}

	Font *FontModel::derive(int size)
	{
		return (new Font(this, this->ftFace, size));
	}

}
