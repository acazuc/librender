#ifndef LIBRENDER_DRAWABLE_H
# define LIBRENDER_DRAWABLE_H

# include "./Context/Context.h"
# include "./DrawableBase.h"

namespace librender
{

	class Drawable : public virtual DrawableBase
	{

	protected:
		VertexArray vertexArray;
		Context &context;
		Buffer texCoords;
		Buffer vertexes;
		Buffer indices;
		Buffer colors;
		uint32_t shapeType;
		uint8_t buffersChanged;
		bool initialized;

	public:
		Drawable(Context &context);
		~Drawable();
		virtual void draw();
		void requireUpdates(uint8_t updates) override;

	};

}

#endif
