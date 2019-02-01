#ifndef LIBRENDER_DRAWABLE_BATCH_H
# define LIBRENDER_DRAWABLE_BATCH_H

# include "./DrawableBatched.h"
# include "./Drawable.h"

namespace librender
{

	class DrawableBatch : public Drawable
	{

	protected:
		std::vector<DrawableBatched*> childs;
		bool dirtyVertices;
		bool dirtyIndices;
		void rebuildVertices();
		void rebuildIndices();
		bool update();
		void fillIndices(std::vector<uint32_t>::iterator indices) override;
		void fillTexCoords(std::vector<Vec2>::iterator texCoords) override;
		void fillVertexes(std::vector<Vec2>::iterator vertexes) override;
		void fillColors(std::vector<Vec4>::iterator colors) override;

	public:
		DrawableBatch(Context &context);
		~DrawableBatch();
		void draw() override;
		virtual void addChild(DrawableBatched *child);
		virtual void removeChild(DrawableBatched *child);
		virtual void clearChilds();
		inline std::vector<DrawableBatched*> &getChilds() {return this->childs;};
		inline void setDirtyVertices() {this->dirtyVertices = true;};
		inline void setDirtyIndices() {this->dirtyIndices = true;};

	};

}

#endif
