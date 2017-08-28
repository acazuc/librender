#ifndef TEXTURE_H
# define TEXTURE_H

# include "Color.h"
# include <cstdint>
# include <string>

namespace librender
{

	class Texture
	{

	private:
		uint32_t width;
		uint32_t height;
		uint textureID;
		uint8_t sprites;

	public:
		Texture(char *data, uint32_t width, uint32_t height);
		~Texture();
		void bind();
		inline int32_t getWidth() {return (this->width);};
		inline int32_t getHeight() {return (this->height);};
		inline uint getTextureID() {return (this->textureID);};

	};

}

#endif
