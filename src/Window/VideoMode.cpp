#include "VideoMode.h"

namespace librender
{

	VideoMode::VideoMode(int32_t refreshRate, int32_t redBits, int32_t greenBits, int32_t blueBits, int32_t width, int32_t height)
	: refreshRate(refreshRate)
	, redBits(redBits)
	, greenBits(greenBits)
	, blueBits(blueBits)
	, width(width)
	, height(height)
	{
		//Empty
	}

	int32_t VideoMode::getRefreshRate()
	{
		return (this->refreshRate);
	}

	int32_t VideoMode::getRedBits()
	{
		return (this->redBits);
	}

	int32_t VideoMode::getGreenBits()
	{
		return (this->greenBits);
	}

	int32_t VideoMode::getBlueBits()
	{
		return (this->blueBits);
	}

	int32_t VideoMode::getWidth()
	{
		return (this->width);
	}

	int32_t VideoMode::getHeight()
	{
		return (this->height);
	}

}
