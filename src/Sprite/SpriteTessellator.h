#ifndef SPRITE_TESSELLATOR_H
# define SPRITE_TESSELLATOR_H

# include "../Vec/Vec4.h"
# include "../Texture/Texture.h"
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
		void addQuad(Vec2 pos, Vec2 size, Vec2 texOrg, Vec2 texSize, Vec4 color);
		inline void setTexture(Texture *texture) {this->texture = texture;};
		inline Texture *getTexture() {return (this->texture);};

	};

}

#endif
