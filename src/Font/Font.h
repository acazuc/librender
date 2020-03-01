#ifndef LIBRENDER_FONT_H
# define LIBRENDER_FONT_H

# include "../Texture/Texture.h"
# include "./FontModel.h"
# include "../Color.h"
# include "./Glyph.h"
# include <unordered_map>
# include <ft2build.h>
# include FT_FREETYPE_H
# include <cstdint>
# include <string>
# include <vector>

namespace librender
{

	struct FontClusterLine
	{
		uint32_t width;
		uint32_t height;
		uint32_t y;
	};

	struct FontCluster
	{
		std::vector<FontClusterLine> lines;
		uint32_t height;
		uint32_t width;
		uint32_t x;
		uint32_t y;
		bool findPlace(uint32_t width, uint32_t height, uint32_t *x, uint32_t *y);
	};

	struct FontTmpGlyph
	{
		uint32_t character;
		std::vector<char> datas;
	};

	class Font
	{

	private:
		FontModel &parent;
		std::unordered_map<uint32_t, Glyph> glyphs;
		std::vector<FontTmpGlyph> tmpGlyphs;
		std::vector<FontCluster> clusters;
		Texture texture;
		uint32_t textureHeight;
		uint32_t textureWidth;
		uint32_t revision;
		uint32_t height;
		uint32_t size;
		bool alphaTexture;
		Glyph *loadGlyph(uint32_t character);
		void createCluster();
		bool findPlace(uint32_t width, uint32_t height, uint32_t *x, uint32_t *y);
		void charCopy(char *data, uint32_t x, uint32_t y, uint32_t width, Glyph &glyph, char *glyphData);
		void glArrayQuad(int32_t texX, int32_t texY, int32_t texWidth, int32_t texHeight, float *texCoords);

	public:
		Font(FontModel &parent, uint32_t size, bool alphaTexture = true);
		~Font();
		Glyph *getGlyph(uint32_t character);
		int32_t getWidth(std::string &text);
		int32_t getHeight(std::string &text);
		void bind();
		void glUpdate();
		void glChar(uint32_t character, float *texCoords);
		void glGlyph(Glyph *glyph, float *texCoords);
		inline Texture &getTexture() {return this->texture;};
		inline int32_t getLineHeight() {return this->height;};
		inline uint32_t getRevision() {return this->revision;};

	};

}

#endif
