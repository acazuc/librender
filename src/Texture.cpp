#include "Texture.h"

namespace librender
{

	Texture::Texture(char *data, uint32_t width, uint32_t height)
	{
		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		this->width = width;
		this->height = height;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->textureID);
	}

	void Texture::drawPart(int32_t x, int32_t y, int32_t width, int32_t height, int32_t texXOrg, int32_t texYOrg, int32_t texCoWidth, int32_t texCoHeight)
	{
		float xFrom = texXOrg / static_cast<float>(getWidth());
		float xTo = (texXOrg + texCoWidth) / static_cast<float>(getWidth());
		float yFrom = texYOrg / static_cast<float>(getHeight());
		float yTo = (texYOrg+texCoHeight) / static_cast<float>(getHeight());
		glTexCoord2f(xFrom, yFrom);
		glVertex2f(x, y);
		glTexCoord2f(xFrom, yTo);
		glVertex2f(x, y + height);
		glTexCoord2f(xTo, yTo);
		glVertex2f(x + width, y + height);
		glTexCoord2f(xTo, yFrom);
		glVertex2f(x + width, y);
	}

	void Texture::drawPart(uint8_t sprite, int32_t x, int32_t y, int32_t width, int32_t height)
	{
		float xFrom = sprite / static_cast<float>(this->sprites);
		float xTo = (sprite + 1) / static_cast<float>(this->sprites);
		float yFrom = 0;
		float yTo = 1;
		glTexCoord2f(xFrom, yFrom);
		glVertex2f(x, y);
		glTexCoord2f(xFrom, yTo);
		glVertex2f(x, y + height);
		glTexCoord2f(xTo, yTo);
		glVertex2f(x + width, y + height);
		glTexCoord2f(xTo, yFrom);
		glVertex2f(x + width, y);
	}

	void Texture::draw(uint8_t sprite, int32_t x, int32_t y, int32_t width, int32_t height, Color *color)
	{
		bind();
		glBegin(GL_QUADS);
		color->bind();
		drawPart(sprite, x, y, width, height);
		glEnd();
	}

	void Texture::draw(uint8_t sprite, int32_t x, int32_t y, int32_t width, int32_t height, float alpha)
	{
		bind();
		glBegin(GL_QUADS);
		glColor4f(1, 1, 1, alpha);
		drawPart(sprite, x, y, width, height);
		glEnd();
	}

	void Texture::draw(int32_t x, int32_t y, int32_t width, int32_t height, Color *color)
	{
		draw(0, x, y, width, height, color);
	}

	void Texture::draw(int32_t x, int32_t y, int32_t width, int32_t height, float alpha)
	{
		draw(0, x, y, width, height, alpha);
	}

	void Texture::draw(uint8_t sprite, int32_t x, int32_t y, Color *color)
	{
		draw(sprite, x, y, getWidth(), getHeight(), color);
	}

	void Texture::draw(uint8_t sprite, int32_t x, int32_t y, float alpha)
	{
		draw(sprite, x, y, getWidth(), getHeight(), alpha);
	}

	void Texture::draw(int32_t x, int32_t y, Color *color)
	{
		draw(0, x, y, getWidth(), getHeight(), color);
	}

	void Texture::draw(int32_t x, int32_t y, float alpha)
	{
		draw(0, x, y, getWidth(), getHeight(), alpha);
	}

}
