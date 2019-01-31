#ifndef LIBRENDER_DRAWABLE_BATCHED_H
# define LIBRENDER_DRAWABLE_BATCHED_H

# include "./DrawableBase.h"

namespace librender
{

	class DrawableBatch;

	class DrawableBatched : public virtual DrawableBase
	{

	protected:
		DrawableBatch *parent;
		uint8_t changes;
		void setVerticesNumber(uint32_t verticesNumber) override;
		void setIndicesNumber(uint32_t indicesNumber) override;

	public:
		DrawableBatched();
		~DrawableBatched();
		void requireUpdates(uint8_t updates) override;
		void update();
		virtual void setParent(DrawableBatch *parent);
		void setX(float x);
		float getX();
		void setY(float y);
		float getY();
		void setScaleX(float scaleX);
		void setScaleY(float scaleY);
		inline uint8_t getChanges() {return this->changes;};
		inline void removeChanges(uint8_t changes) {this->changes &= ~changes;};
		void addChanges(uint8_t changes);

	};

}

#endif
