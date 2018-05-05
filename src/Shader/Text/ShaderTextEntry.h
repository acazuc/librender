#ifndef LIBRENDER_SHADER_TEXT_ENTRY_H
# define LIBRENDER_SHADER_TEXT_ENTRY_H

# include "../../Font/Font.h"
# include "../../Vec/Vec4.h"
# include "../../Vec/Vec2.h"
# include "../../Color.h"
# include <cstdint>
# include <string>

namespace librender
{

	class ShaderTextEntry
	{

	protected:
		std::string text;
		Color shadowColor;
		Color color;
		Vec2 *texCoords;
		Vec2 *vertexes;
		Vec4 *colors;
		Vec2 scale;
		Vec2 pos;
		uint32_t verticesNumber;
		uint32_t fontRevision;
		uint32_t charsNumber;
		uint8_t updatesRequired;
		int16_t shadowSize;
		int32_t lineHeight;
		int32_t maxWidth;
		int32_t shadowX;
		int32_t shadowY;
		int32_t height;
		int32_t width;
		float opacity;
		bool mustCalcHeight;
		bool mustCalcWidth;
		inline void updateTexCoords() {fillTexCoords(this->texCoords);};
		inline void updateVertexes() {fillVertexes(this->vertexes);};
		inline void updateColors() {fillColors(this->colors);};
		void fillTexCoords(Vec2 *texCoords);
		void fillVertexes(Vec2 *vertexes);
		void fillColors(Vec4 *colors);
		virtual void resize(uint32_t len);

	public:
		ShaderTextEntry();
		~ShaderTextEntry();
		virtual void requireUpdates(uint8_t updates);
		virtual void update();
		void setText(std::string &text);
		inline std::string &getText() {return (this->text);};
		inline Vec2 *getTexCoords() {return (this->texCoords);};
		inline Vec2 *getVertexes() {return (this->vertexes);};
		inline Vec4 *getColors() {return (this->colors);};
		void setShadowColor(Color &color);
		inline Color &getShadowColor() {return (this->shadowColor);};
		void setColor(Color &color);
		inline Color &getColor() {return (this->color);};
		inline virtual Font *getFont() {return (nullptr);};
		inline uint32_t getVerticesNumber() {return (this->verticesNumber);};
		inline void setLineHeight(uint32_t lineHeight) {this->lineHeight = lineHeight;};
		int32_t getLineHeight();
		void setShadowSize(int16_t shadowSize);
		inline int16_t getShadowSize() {return (this->shadowSize);};
		inline void setShadowPos(int32_t x, int32_t y) {setShadowX(x);setShadowY(y);};
		void setShadowX(int32_t shadowX);
		inline int32_t getShadowX() {return (this->shadowX);};
		void setShadowY(int32_t shadowY);
		inline int32_t getShadowY() {return (this->shadowY);};
		void setOpacity(float opacity);
		inline float getOpacity() {return (this->opacity);};
		virtual void setScaleX(float scaleX);
		inline float getScaleX() {return (this->scale.x);};
		virtual void setScaleY(float scaleY);
		inline float getScaleY() {return (this->scale.y);};
		void setScale(float scale) {setScaleX(scale);setScaleY(scale);};
		void setMaxWidth(int32_t width);
		inline int32_t getMaxWidth() {return (this->maxWidth);};
		inline virtual void setX(float x) {this->pos.x = x;};
		inline float getX() {return (this->pos.x);};
		inline virtual void setY(float y) {this->pos.y = y;};
		inline float getY() {return (this->pos.y);};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void recalcWidth() {this->mustCalcWidth = true;};
		inline void recalcHeight() {this->mustCalcHeight = true;};
		int32_t getWidth();
		int32_t getHeight();

	};

}

#endif
