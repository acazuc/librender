#ifndef LIBRENDER_SPRITE_BASE_H
# define LIBRENDER_SPRITE_BASE_H

# include "../Texture/Texture.h"
# include "../DrawableBase.h"
# include <array>

namespace librender
{

	class SpriteBase : public virtual DrawableBase
	{

	private:
		std::array<Vec4, 4> colors;
		Vec2 texTopLeft;
		Vec2 texBotRight;
		Vec2 size;

	public:
		SpriteBase();
		void fillIndices(std::vector<uint32_t>::iterator indices) override;
		void fillTexCoords(std::vector<Vec2>::iterator texCoords) override;
		void fillVertexes(std::vector<Vec2>::iterator vertexes) override;
		void fillColors(std::vector<Vec4>::iterator colors) override;
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
		void setTexLeft(float left);
		void setTexRight(float right);
		void setTexTop(float top);
		void setTexBot(float bot);
		void setTexTopBot(Vec2 topBot);
		void setTexLeftRight(Vec2 leftRight);
		void setTexTopLeft(Vec2 topLeft);
		void setTexBotRight(Vec2 botRight);
		void setWidth(float width);
		float getWidth();
		void setHeight(float height);
		float getHeight();
		void setSize(float width, float height);
		int32_t getTextureWidth();
		int32_t getTextureHeight();

	};

}

#endif
