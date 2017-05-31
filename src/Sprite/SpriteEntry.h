#ifndef LIBRENDER_SPRITE_ENTRY_H
# define LIBRENDER_SPRITE_ENTRY_H

# include "../Texture.h"
# include "../GL.h"

namespace librender
{

	class SpriteEntry
	{

	protected:
		GLfloat texCoords[8];
		GLfloat vertex[8];
		GLfloat colors[16];
		uint32_t verticesNumber;
		uint8_t updatesRequired;
		float opacity;
		float scaleX;
		float scaleY;
		float x;
		float y;
		void fillTexCoords(GLfloat *texCoords);
		void fillVertex(GLfloat *vertex);
		void fillColors(GLfloat *colors);

	public:
		SpriteEntry();
		~SpriteEntry();
		virtual void update();
		inline GLfloat *getTexCoords() {return (this->texCoords);};
		inline GLfloat *getVertex() {return (this->vertex);};
		inline GLfloat *getColors() {return (this->colors);};
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
		void setOpacity(float opacity);
		inline float getOpacity() {return (this->opacity);};
		void setScaleX(float scaleX);
		inline float getScaleX() {return (this->scaleX);};
		void setScaleY(float scaleY);
		inline float getScaleY() {return (this->scaleY);};
		void setScale(float scale) {setScaleX(scale);setScaleY(scale);};
		void setTexX(float texX);
		void setTexY(float texY);
		void setTexWidth(float texWidth);
		void setTexHeight(float texHeight);
		void setWidth(float width);
		void setHeight(float height);
		inline virtual void setX(float x) {this->x = x;};
		inline float getX() {return (this->x);};
		inline virtual void setY(float y) {this->y = y;};
		inline float getY() {return (this->y);};
		inline void setPos(float x, float y) {setX(x);setY(y);};

	};

}

#endif
