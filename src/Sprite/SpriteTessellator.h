#ifndef SPRITE_TESSELLATOR_H
# define SPRITE_TESSELLATOR_H

# include "../Texture.h"
# include "../GL.h"
# include <glm/vec4.hpp>
# include <glm/vec2.hpp>
# include <vector>

namespace librender
{

	class SpriteTessellator
	{

	private:
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec2> vertexes;
		std::vector<glm::vec4> colors;
		Texture *texture;

	public:
		SpriteTessellator();
		void clear();
		void draw();
		void add(glm::vec2 vertex, glm::vec2 texCoords, glm::vec4 color);
		inline void setTexture(Texture *texture) {this->texture = texture;};

	};

}

#endif
