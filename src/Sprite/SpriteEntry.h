#ifndef LIBRENDER_SPRITE_ENTRY_H
# define LIBRENDER_SPRITE_ENTRY_H

# include "../Vec/Vec4.h"
# include "../Texture.h"
# include <cstdlib>

namespace librender
{

	class SpriteEntry
	{

	protected:
		Vec2 texCoords[4];
		Vec2 vertexes[4];
		Vec4 colors[4];
		Vec2 scale;
		Vec2 pos;
		uint32_t verticesNumber;
		uint8_t updatesRequired;
		void fillTexCoords(Vec2 *texCoords);
		void fillVertexes(Vec2 *vertexes);
		void fillColors(Vec4 *colors);

	public:
		SpriteEntry();
		virtual ~SpriteEntry();
		virtual void update();
		inline Vec2 *getTexCoords() {return (this->texCoords);};
		inline Vec2 *getVertexes() {return (this->vertexes);};
		inline Vec4 *getColors() {return (this->colors);};
		void setColor(Color &color);
		void setTopColor(Color &color);
		void setBotColor(Color &color);
		void setLeftColor(Color &color);
		void setRightColor(Color &color);
		void setTopLeftColor(Color &color);
		void setTopRightColor(Color &color);
		void setBotLeftColor(Color &color);
		void setBotRightColor(Color &color);
		virtual Texture *getTexture() {return (NULL);};
		inline uint32_t getVerticesNumber() {return (this->verticesNumber);};
		void setScaleX(float scaleX);
		inline float getScaleX() {return (this->scale.x);};
		void setScaleY(float scaleY);
		inline float getScaleY() {return (this->scale.y);};
		void setScale(float scale) {setScaleX(scale);setScaleY(scale);};
		void setTexX(float texX);
		void setTexY(float texY);
		void setTexPos(float texX, float texY);
		void setTexWidth(float texWidth);
		void setTexHeight(float texHeight);
		void setTexSize(float texWidth, float texHeight);
		virtual void setWidth(float width);
		virtual void setHeight(float height);
		void setSize(float width, float height);
		inline virtual void setX(float x) {this->pos.x = x;};
		inline float getX() {return (this->pos.x);};
		inline virtual void setY(float y) {this->pos.y = y;};
		inline float getY() {return (this->pos.y);};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		int32_t getTextureWidth();
		int32_t getTextureHeight();

	};

}

#endif
