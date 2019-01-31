#ifndef TEXTURE_H
# define TEXTURE_H

# include "../Color.h"
# include <cstdint>

namespace librender
{

	enum TextureFilterType
	{
		TEXTURE_FILTER_NEAREST,
		TEXTURE_FILTER_LINEAR,
		TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST,
		TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR,
	};

	enum TextureWrapType
	{
		TEXTURE_WRAP_REPEAT,
		TEXTURE_WRAP_MIRRORED_REPEAT,
		TEXTURE_WRAP_CLAMP_TO_EDGE,
		TEXTURE_WRAP_CLAMP_TO_BORDER
	};

	enum TextureFormat
	{
		TEXTURE_BGRA8,
		TEXTURE_RGB8,
		TEXTURE_RGB_DXT1,
		TEXTURE_RGBA_DXT1,
		TEXTURE_RGBA_DXT3,
		TEXTURE_RGBA_DXT5,
	};

	class Texture
	{

	private:
		uint16_t format : 3;
		uint16_t wrapS : 2;
		uint16_t wrapT : 2;
		uint16_t filter : 3;
		uint16_t anisotropicLevel : 5;
		uint16_t generateMipmap : 1;
		uint32_t width;
		uint32_t height;
		uint32_t id;
		void *data;

	public:
		Texture();
		~Texture();
		void bind();
		void setData(void *data, uint32_t width, uint32_t height);
		void setMinFilter(enum TextureFilterType type);
		void setMagFilter(enum TextureFilterType type);
		void setFilter(enum TextureFilterType minType, enum TextureFilterType magType);
		void setXWrap(enum TextureWrapType type);
		void setYWrap(enum TextureWrapType type);
		void setWrap(enum TextureWrapType xType, enum TextureWrapType yType);
		inline void setWidth(uint32_t width) {this->width = width;};
		inline int32_t getWidth() {return this->width;};
		inline void setHeight(uint32_t height) {this->height = height;};
		inline int32_t getHeight() {return this->height;};
		inline uint32_t getId() {return this->id;};

	};

}

#endif
