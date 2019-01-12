#ifndef LIBRENDER_DRAWABLE_TESSELLATOR_H
# define LIBRENDER_DRAWABLE_TESSELLATOR_H

# include "./Drawable.h"

namespace librender
{

	class DrawableTessellator : public Drawable
	{

	protected:
		void addPoint(Vec2 vertex, Vec2 texCoords, Vec4 color);

	public:
		void clear();

	};

}

#endif
