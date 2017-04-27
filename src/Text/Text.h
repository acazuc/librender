#ifndef LIBRENDER_TEXT_H
# define LIBRENDER_TEXT_H

# include "../Font/Font.h"
# include "../Color.h"
# include "../GL.h"
# include <cstdint>
# include <string>

namespace librender
{

	class Text
	{

	protected:
		std::string text;
		GLfloat *texCoords;
		GLfloat *vertex;
		GLfloat *colors;
		GLuint buffers[3];
		Color shadowColor;
		Color color;
		Font *font;
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
		void updateVertex();
		void updateTexCoords();
		void updateColors();
		void resize(uint32_t len);

	public:
		Text();
		~Text();
		void draw();
		void setText(std::string &text);
		inline std::string &getText() {return (this->text);};
		void setShadowColor(Color &color);
		inline Color &getShadowColor() {return (this->shadowColor);};
		void setColor(Color &color);
		inline Color &getColor() {return (this->color);};
		void setFont(Font *font);
		inline Font *getFont() {return (this->font);};
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
		void setX(float x) {this->x = x;};
		inline float getX() {return (this->x);};
		void setY(float y) {this->y = y;};
		inline float getY() {return (this->y);};
		void setPos(float x, float y) {setX(x);setY(y);};

	};

}

#endif
