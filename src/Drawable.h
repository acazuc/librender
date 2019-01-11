#ifndef LIBRENDER_DRAWABLE_H
# define LIBRENDER_DRAWABLE_H

# include "./Vec/Vec4.h"
# include "./Vec/Vec2.h"
# include <cstdint>
# include <vector>

namespace librender
{

	class Drawable
	{

	protected:
		std::vector<uint32_t> indices;
		std::vector<Vec2> texCoords;
		std::vector<Vec2> vertexes;
		std::vector<Vec4> colors;
		uint32_t verticesNumber;
		uint32_t indicesNumber;
		uint8_t updatesRequired;
		Vec2 scale;
		Vec2 pos;

	public:
		Drawable();
		virtual ~Drawable() {};
		virtual void draw();
		inline std::vector<uint32_t> &getIndices() {return this->indices;};
		inline std::vector<Vec2> &getTexCoords() {return this->texCoords;};
		inline std::vector<Vec2> &getVertexes() {return this->vertexes;};
		inline std::vector<Vec4> &getColors() {return this->colors;};
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
