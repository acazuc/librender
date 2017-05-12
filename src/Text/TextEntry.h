#ifndef LIBRENDER_TEXT_ENTRY_H
# define LIBRENDER_TEXT_ENTRY_H

# include "../Font/Font.h"
# include "../Color.h"
# include "../GL.h"
# include <cstdint>
# include <string>

namespace librender
{

	class TextEntry
	{

	protected:
		std::string text;
		GLfloat *texCoords;
		GLfloat *vertex;
		GLfloat *colors;
		Color shadowColor;
		Color color;
		uint32_t verticesNumber;
		uint32_t charsNumber;
		uint32_t lineHeight;
		uint8_t updatesRequired;
		int16_t shadowSize;
		int16_t shadowX;
		int16_t shadowY;
		float opacity;
		float scaleX;
		float scaleY;
		float x;
		float y;
		void updateTexCoords() {fillTexCoords(this->texCoords);};
		void updateVertex() {fillVertex(this->vertex);};
		void updateColors() {fillColors(this->colors);};
		void fillTexCoords(GLfloat *texCoords);
		void fillVertex(GLfloat *vertex);
		void fillColors(GLfloat *colors);
		virtual void resize(uint32_t len);

	public:
		TextEntry();
		~TextEntry();
		virtual void update();
		void setText(std::string &text);
		inline std::string &getText() {return (this->text);};
		inline GLfloat *getTexCoords() {return (this->texCoords);};
		inline GLfloat *getVertex() {return (this->vertex);};
		inline GLfloat *getColors() {return (this->colors);};
		void setShadowColor(Color &color);
		inline Color &getShadowColor() {return (this->shadowColor);};
		void setColor(Color &color);
		inline Color &getColor() {return (this->color);};
		virtual Font *getFont() {return (NULL);};
		inline uint32_t getVerticesNumber() {return (this->verticesNumber);};
		inline void setLineHeight(uint32_t lineHeight) {this->lineHeight = lineHeight;};
		inline uint32_t getLineHeight() {return (this->lineHeight);};
		void setShadowSize(int16_t shadowSize);
		inline int16_t getShadowSize() {return (this->shadowSize);};
		void setShadowX(int16_t shadowX);
		inline int16_t getShadowX() {return (this->shadowX);};
		void setShadowY(int16_t shadowY);
		inline int16_t getShadowY() {return (this->shadowY);};
		void setOpacity(float opacity);
		inline float getOpacity() {return (this->opacity);};
		void setScaleX(float scaleX);
		inline float getScaleX() {return (this->scaleX);};
		void setScaleY(float scaleY);
		inline float getScaleY() {return (this->scaleY);};
		void setScale(float scale);
		virtual void setX(float x) {this->x = x;};
		inline float getX() {return (this->x);};
		virtual void setY(float y) {this->y = y;};
		inline float getY() {return (this->y);};
		void setPos(float x, float y) {setX(x);setY(y);};

	};

}

#endif
