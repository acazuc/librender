#ifndef LIBRENDER_FONT_H
# define LIBRENDER_FONT_H

# include "FontModel.h"
# include "FontGlyph.h"
# include "Color.h"
# include "GL.h"
# include <ft2build.h>
# include FT_FREETYPE_H
# include <cstdint>
# include <vector>
# include <string>

namespace librender
{

	class Font
	{

	private:
		static FT_Library ftLib;
		FontGlyph **glyphs;
		FontModel *parent;
		FT_Face ftFace;
		GLuint textureID;
		char **glyphs_datas;
		uint32_t textureHeight;
		uint32_t textureWidth;
		uint32_t height;
		void loadList(int32_t size);
		void createSet();
		void copyChar(int32_t x, int32_t y, char *data, uint32_t size, FontGlyph *glyph, char *glyph_data);
		char *imageCrop(char *data, int32_t size, int32_t height);
		void buildGLTexture(char *data, uint32_t width, uint32_t height);
		void drawQuad(float x, float y, float width, float height, int texX, int texY, int texWidth, int texHeight);
		void glArrayQuad(int texX, int texY, int texWidth, int texHeight, float *texCoords);

	public:
		Font(FontModel *parent, FT_Face ftFace, int size);
		~Font();
		FontGlyph *getGlyph(uint32_t character);
		int32_t getWidth(std::string &text);
		int32_t getHeight(std::string &text);
		inline int32_t getLineHeight() {return (this->height);};
		inline void bind() {glBindTexture(GL_TEXTURE_2D, this->textureID);};
		inline GLuint getTextureId() {return (this->textureID);};
		void drawBegin();
		void drawEnd();
		void drawChar(float x, float y, uint32_t character, Color &color, float scaleX = 1, float scaleY = 1, float opacity = 1);
		void drawCharPart(float x, float y, uint32_t character, float scaleX = 1, float scaleY = 1);
		void glArrayCharPart(uint32_t character, float *texCoords);
		void drawStringPart(float x, float y, std::string &text, Color &color, float opacity = 1);
		void drawStringPart(float x, float y, std::string &text, Color &color, float scaleX, float scaleY, float opacity = 1);
		void drawString(float x, float y, std::string &text, Color &color, float opacity = 1);
		void drawString(float x, float y, std::string &text, Color &color, float scaleX, float scaleY, float opacity = 1);
		void drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float opacity = 1);
		void drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float scaleX, float scaleY, float opacity);
		void drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY);
		void drawStringShadow(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY, float scaleX, float scaleY, float opacity = 1);
		void drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float opacity = 1);
		void drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float scaleX, float scaleY, float opacity);
		void drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY);
		void drawStringShadowPart(float x, float y, std::string &text, Color &color, Color &shadowColor, float shadowSize, float shadowX, float shadowY, float scaleX, float scaleY, float opacity = 1);

	};

}

#endif
