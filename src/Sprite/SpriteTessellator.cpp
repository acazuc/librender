#include "SpriteTessellator.h"
#include "../DrawableBuffers.h"

namespace librender
{

	SpriteTessellator::SpriteTessellator(Context &context)
	: DrawableTessellator(context)
	, texture(nullptr)
	{
	}

	void SpriteTessellator::draw()
	{
		if (this->texture)
			this->buffers |= DRAWABLE_BUFFER_TEX_COORDS;
		else
			this->buffers &= ~DRAWABLE_BUFFER_TEX_COORDS;
		this->context.setSamplerTexture(0, this->texture);
		DrawableTessellator::draw();
	}

	void SpriteTessellator::addQuad(Vec2 pos, Vec2 size, Vec2 texPos, Vec2 texSize, Vec4 color)
	{
		Vec2 org(pos);
		Vec2 dst(pos + size);
		Vec2 texOrg(texPos);
		Vec2 texDst(texPos + texSize);
		uint32_t base = this->vertexes.size();
		addPoint(Vec2(org.x, org.y), Vec2(texOrg.x, texOrg.y), color);
		addPoint(Vec2(dst.x, org.y), Vec2(texDst.x, texOrg.y), color);
		addPoint(Vec2(dst.x, dst.y), Vec2(texDst.x, texDst.y), color);
		addPoint(Vec2(org.x, dst.y), Vec2(texOrg.x, texDst.y), color);
		addIndice(base + 0);
		addIndice(base + 3);
		addIndice(base + 1);
		addIndice(base + 2);
		addIndice(base + 1);
		addIndice(base + 3);
	}

}
