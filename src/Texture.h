#ifndef TEXTURE_H
# define TEXTURE_H

# include "Color.h"
# include "GL.h"
# include <cstdint>
# include <string>

namespace librender
{

	class Texture
	{

	private:
		uint32_t width;
		uint32_t height;
		GLuint textureID;
		uint8_t sprites;

	public:
		Texture(char *data, uint32_t width, uint32_t height);
		~Texture();
		inline int32_t getWidth() {return (this->width);};
		inline int32_t getHeight() {return (this->height);};
		inline GLuint getTextureID() {return (this->textureID);};
		inline void bind() {glBindTexture(GL_TEXTURE_2D, this->textureID);};

	};

}

#endif
