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
		Color color;
		uint32_t verticesNumber;
		uint8_t updatesRequired;
		float opacity;
		float scaleX;
		float scaleY;
		float x;
		float y;
		inline void updateTexCoords() {fillTexCoords(this->texCoords);};
		inline void updateVertex() {fillVertex(this->vertex);};
		inline void updateColors() {fillColors(this->colors);};
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
		inline Color &getColor() {return (this->color);};
		virtual Texture *getTexture() {return (NULL);};
		inline uint32_t getVerticesNumber() {return (this->verticesNumber);};
		void setOpacity(float opacity);
		inline float getOpacity() {return (this->opacity);};
		void setScaleX(float scaleX);
		inline float getScaleX() {return (this->scaleX);};
		void setScaleY(float scaleY);
		inline float getScaleY() {return (this->scaleY);};
		void setScale(float scale) {setScaleX(scale);setScaleY(scale);};
		inline virtual void setX(float x) {this->x = x;};
		inline float getX() {return (this->x);};
		inline virtual void setY(float y) {this->y = y;};
		inline float getY() {return (this->y);};
		inline void setPos(float x, float y) {setX(x);setY(y);};

	};

}

#endif
