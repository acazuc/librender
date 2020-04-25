#ifndef LIBRENDER_FONT_H
# define LIBRENDER_FONT_H

# include "../Texture/Texture.h"
# include "./FontModel.h"
# include "./FontAtlas.h"
# include "../Color.h"
# include "./Glyph.h"
# include <cstdint>
# include <string>

namespace librender
{

	class Font
	{

	private:
		FontModel &parent;
		FontAtlas atlas;
		Texture texture;
		uint32_t lastAtlasRevision;
		uint32_t revision;
		uint32_t height;
		uint32_t size;
		Glyph *loadGlyph(uint32_t codepoint);
		void glArrayQuad(int32_t texX, int32_t texY, int32_t texWidth, int32_t texHeight, float *texCoords);

	public:
		Font(FontModel &parent, uint32_t size, bool alphaTexture = true);
		~Font();
		Glyph *getGlyph(uint32_t codepoint);
		int32_t getWidth(const std::string &text);
		int32_t getHeight(const std::string &text);
		void bind();
		void glUpdate();
		void glChar(uint32_t codepoint, float *texCoords);
		void glGlyph(Glyph *glyph, float *texCoords);
		inline Texture &getTexture() {return this->texture;};
		inline int32_t getLineHeight() {return this->height;};
		inline uint32_t getRevision() {return this->atlas.getRevision();};

	};

}

#endif
