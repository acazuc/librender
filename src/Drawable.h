#ifndef LIBRENDER_DRAWABLE_H
# define LIBRENDER_DRAWABLE_H

# include "./Context/Context.h"
# include "./DrawableBase.h"

namespace librender
{

	class Drawable : public virtual DrawableBase
	{

	protected:
		/*std::vector<uint32_t> indices;
		std::vector<Vec2> texCoords;
		std::vector<Vec2> vertexes;
		std::vector<Vec4> colors;*/
		VertexArray vertexArray;
		Buffer texCoords;
		Buffer vertexes;
		Buffer indices;
		Buffer colors;
		Context *context;
		uint32_t shapeType;
		uint8_t buffersChanged;
		bool initialized;

	public:
		Drawable(Context *context);
		~Drawable();
		virtual void draw();
		void requireUpdates(uint8_t updates) override;

	};

}

#endif
