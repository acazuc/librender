#ifndef LIBRENDER_SPRITE_BASE_H
# define LIBRENDER_SPRITE_BASE_H

# include "../Texture/Texture.h"
# include "../DrawableBase.h"

namespace librender
{

	class SpriteBase : public virtual DrawableBase
	{

	private:
		Vec2 size;
		void updateVertexes();

	public:
		SpriteBase();
		void setColor(Color color);
		void setTopColor(Color color);
		void setBotColor(Color color);
		void setLeftColor(Color color);
		void setRightColor(Color color);
		void setTopLeftColor(Color color);
		void setTopRightColor(Color color);
		void setBotLeftColor(Color color);
		void setBotRightColor(Color color);
		virtual Texture *getTexture() {return nullptr;};
		void setTexX(float texX);
		float getTexX();
		void setTexY(float texY);
		float getTexY();
		void setTexPos(float texX, float texY);
		void setTexWidth(float texWidth);
		float getTexWidth();
		void setTexHeight(float texHeight);
		float getTexHeight();
		inline void setTexSize(float texWidth, float texHeight) {setTexWidth(texWidth);setTexHeight(texHeight);};
		virtual void setWidth(float width);
		float getWidth();
		virtual void setHeight(float height);
		float getHeight();
		inline void setSize(float width, float height) {setWidth(width);setHeight(height);};
		int32_t getTextureWidth();
		int32_t getTextureHeight();

	};

}

#endif
