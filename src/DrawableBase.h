#ifndef LIBRENDER_DRAWABLE_BASE_H
# define LIBRENDER_DRAWABLE_BASE_H

# include "./Drawable.h"

namespace librender
{

	class DrawableBase : public Drawable
	{

	protected:
		inline virtual void updateTexCoords() {};
		inline virtual void updateVertexes() {};
		inline virtual void updateIndices() {};
		inline virtual void updateColors() {};
		virtual void updateBuffers();

	public:
		virtual void resize(uint32_t vertices, uint32_t indices);

	};

}

#endif
