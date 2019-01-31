#ifndef LIBRENDER_DRAWABLE_BASE_H
# define LIBRENDER_DRAWABLE_BASE_H

# include "./Vec/Vec4.h"
# include "./Vec/Vec2.h"
# include <cstdint>
# include <vector>

namespace librender
{

	class DrawableBase
	{

	protected:
		Vec2 scale;
		Vec2 pos;
		uint32_t verticesNumber;
		uint32_t indicesNumber;
		uint8_t updatesRequired;
		uint8_t buffers;
		virtual void updateTexCoords() {};
		virtual void updateVertexes() {};
		virtual void updateIndices() {};
		virtual void updateColors() {};
		virtual void setVerticesNumber(uint32_t verticesNumber);
		virtual void setIndicesNumber(uint32_t indicesNumber);
		virtual void updateBuffers();

	public:
		DrawableBase();
		virtual ~DrawableBase() {};
		virtual void fillIndices(std::vector<uint32_t>::iterator indices);
		virtual void fillTexCoords(std::vector<Vec2>::iterator texCoords);
		virtual void fillVertexes(std::vector<Vec2>::iterator vertexes);
		virtual void fillColors(std::vector<Vec4>::iterator colors);
		inline uint32_t getVerticesNumber() {return this->verticesNumber;};
		inline uint32_t getIndicesNumber() {return this->indicesNumber;};
		virtual void requireUpdates(uint8_t updates);
		inline virtual void setScaleX(float scaleX) {this->scale.x = scaleX;};
		inline float getScaleX() {return this->scale.x;};
		inline virtual void setScaleY(float scaleY) {this->scale.y = scaleY;};
		inline float getScaleY() {return this->scale.y;};
		inline void setScale(float scaleX, float scaleY) {setScaleX(scaleX);setScaleY(scaleY);};
		inline void setScale(float scale) {setScaleX(scale);setScaleY(scale);};
		inline virtual void setX(float x) {this->pos.x = x;};
		inline float getX() {return this->pos.x;};
		inline virtual void setY(float y) {this->pos.y = y;};
		inline float getY() {return this->pos.y;};
		inline void setPos(float x, float y) {setX(x);setY(y);};

	};

}

#endif
