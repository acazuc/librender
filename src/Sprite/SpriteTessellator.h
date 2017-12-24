#ifndef SPRITE_TESSELLATOR_H
# define SPRITE_TESSELLATOR_H

# include "../Vec/Vec4.h"
# include "../Texture.h"
# include "../GL.h"
# include <vector>

namespace librender
{

	class SpriteTessellator
	{

	private:
		std::vector<Vec2> texCoords;
		std::vector<Vec2> vertexes;
		std::vector<Vec4> colors;
		Texture *texture;

	public:
		SpriteTessellator();
		void clear();
		void draw();
		void add(Vec2 vertex, Vec2 texCoords, Vec4 color);
		inline void setTexture(Texture *texture) {this->texture = texture;};

	};

}

#endif
