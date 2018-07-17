#ifndef TEXT_TESSELLATOR_H
# define TEXT_TESSELLATOR_H

# include "../Font/Font.h"
# include "../Vec/Vec4.h"
# include "../Vec/Vec2.h"
# include <vector>

namespace librender
{

	class TextTessellator
	{

	private:
		std::vector<Vec2> texCoords;
		std::vector<Vec2> vertexes;
		std::vector<Vec4> colors;
		Font *font;

	public:
		TextTessellator();
		void clear();
		void draw();
		void add(Vec2 vertex, Vec2 texCoords, Vec4 color);
		void addGlyph(Glyph *glyph, Vec2 pos, Vec4 color);
		void addChar(uint32_t character, Vec2 pos, Vec4 color);
		inline void setFont(Font *font) {this->font = font;};
		inline Font *getFont() {return this->font;};

	};

}

#endif
