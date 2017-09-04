#ifndef LIBRENDER_SPRITE_ENTRY_H
# define LIBRENDER_SPRITE_ENTRY_H

# include "../Texture.h"
# include <cstdlib>

namespace librender
{

	class SpriteEntry
	{

	protected:
		float texCoords[8];
		float vertex[8];
		float colors[16];
		uint32_t verticesNumber;
		uint8_t updatesRequired;
		float scaleX;
		float scaleY;
		float x;
		float y;
		void fillTexCoords(float *texCoords);
		void fillVertex(float *vertex);
		void fillColors(float *colors);

	public:
		SpriteEntry();
		~SpriteEntry();
		virtual void update();
		inline float *getTexCoords() {return (this->texCoords);};
		inline float *getVertex() {return (this->vertex);};
		inline float *getColors() {return (this->colors);};
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
		inline float getScaleX() {return (this->scaleX);};
		void setScaleY(float scaleY);
		inline float getScaleY() {return (this->scaleY);};
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
		inline virtual void setX(float x) {this->x = x;};
		inline float getX() {return (this->x);};
		inline virtual void setY(float y) {this->y = y;};
		inline float getY() {return (this->y);};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		int32_t getTextureWidth();
		int32_t getTextureHeight();

	};

}

#endif
