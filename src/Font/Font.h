#ifndef LIBRENDER_FONT_H
# define LIBRENDER_FONT_H

# include "../Texture/Texture.h"
# include "FontModel.h"
# include "FontGlyph.h"
# include "../Color.h"
# include <ft2build.h>
# include FT_FREETYPE_H
# include <cstdint>
# include <string>

namespace librender
{

	class Font
	{

	private:
		static FT_Library ftLib;
		FontGlyph **glyphs;
		FontModel *parent;
		Texture texture;
		FT_Face ftFace;
		char **glyphs_datas;
		uint32_t textureHeight;
		uint32_t textureWidth;
		uint32_t height;
		void loadList(int32_t size);
		void createSet();
		void copyChar(int32_t x, int32_t y, char *data, uint32_t size, FontGlyph *glyph, char *glyph_data);
		char *imageCrop(char *data, int32_t size, int32_t height);
		void buildGLTexture(char *data, uint32_t width, uint32_t height);
		void glArrayQuad(int32_t texX, int32_t texY, int32_t texWidth, int32_t texHeight, float *texCoords);

	public:
		Font(FontModel *parent, FT_Face ftFace, int size);
		~Font();
		FontGlyph *getGlyph(uint32_t character);
		int32_t getWidth(std::string &text);
		int32_t getHeight(std::string &text);
		void bind();
		void glChar(uint32_t character, float *texCoords);
		void glGlyph(FontGlyph *glyph, float *texCoords);
		inline Texture &getTexture() {return (this->texture);};
		inline int32_t getLineHeight() {return (this->height);};

	};

}

#endif
