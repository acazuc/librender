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
		void drawPart(int32_t x, int32_t y, int32_t width, int32_t height, int32_t texXOrg, int32_t texYOrg, int32_t texCoWidth, int32_t texCoHeight);
		void drawPart(uint8_t sprite, int32_t x, int32_t y, int32_t width, int32_t height);
		void draw(uint8_t sprite, int32_t x, int32_t y, int32_t width, int32_t height, Color *color);
		void draw(uint8_t sprite, int32_t x, int32_t y, int32_t width, int32_t height, float alpha = 1);
		void draw(int32_t x, int32_t y, int32_t width, int32_t height, Color *color);
		void draw(int32_t x, int32_t y, int32_t width, int32_t height, float alpha = 1);
		void draw(uint8_t sprite, int32_t x, int32_t y, Color *color);
		void draw(uint8_t sprite, int32_t x, int32_t y, float alpha = 1);
		void draw(int32_t x, int32_t y, Color *color);
		void draw(int32_t x, int32_t y, float alpha = 1);
		inline int32_t getWidth() {return (this->width);};
		inline int32_t getHeight() {return (this->height);};
		inline GLuint getTextureID() {return (this->textureID);};
		inline void bind() {glBindTexture(GL_TEXTURE_2D, this->textureID);};

	};

}

#endif
