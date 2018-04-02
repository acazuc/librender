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
	}

	Font *FontModel::derive(uint32_t size)
	{
		return (new Font(*this, size));
	}

}
