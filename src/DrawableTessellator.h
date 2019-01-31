#ifndef LIBRENDER_DRAWABLE_TESSELLATOR_H
# define LIBRENDER_DRAWABLE_TESSELLATOR_H

# include "./Drawable.h"

namespace librender
{

	class DrawableTessellator : public Drawable
	{

	protected:
		std::vector<uint32_t> indices;
		std::vector<Vec2> texCoords;
		std::vector<Vec2> vertexes;
		std::vector<Vec4> colors;
		void addPoint(Vec2 vertex, Vec2 texCoords, Vec4 color);
		void addIndice(uint32_t indice);

	public:
		DrawableTessellator(Context *context);
		void clear();

	};

}

#endif
