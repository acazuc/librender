#include "FontModel.h"
#include "Font.h"

namespace librender
{

	FT_Library FontModel::ftLib = nullptr;

	FontModel::FontModel(Context &context, std::string filename)
	: context(context)
	{
		if (!FontModel::ftLib)
		{
			if (FT_Init_FreeType(&FontModel::ftLib))
				throw std::exception();
		}
		if (FT_New_Face(FontModel::ftLib, filename.c_str(), 0, &this->ftFace))
			throw std::exception();
		_load();
	}

	FontModel::FontModel(Context &context, char *data, size_t len)
	: context(context)
	{
		if (!FontModel::ftLib)
		{
			if (FT_Init_FreeType(&FontModel::ftLib))
				throw std::exception();
		}
		if (FT_New_Memory_Face(FontModel::ftLib, reinterpret_cast<FT_Byte*>(data), len, 0, &this->ftFace))
			throw std::exception();
		_load();
	}

	FontModel::~FontModel()
	{
		if (FontModel::ftLib)
		{
			FT_Done_FreeType(FontModel::ftLib);
			FontModel::ftLib = nullptr;
		}
	}

	void FontModel::_load()
	{
		if (FT_Select_Charmap(this->ftFace, ft_encoding_unicode))
			throw std::exception();
	}

	Font *FontModel::derive(uint32_t size)
	{
		return new Font(*this, size);
	}

	bool FontModel::setSize(uint32_t size)
	{
		if (size == this->ftFace->size->metrics.x_ppem)
			return true;
		if (FT_Set_Pixel_Sizes(this->ftFace, 0, size))
			return false;
		return true;
	}

}
