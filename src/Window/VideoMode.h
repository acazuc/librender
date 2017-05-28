#ifndef LIBRENDER_VIDEO_MODE_H
# define LIBRENDER_VIDEO_MODE_H

# include <cstdint>

namespace librender
{

	class VideoMode
	{

	private:
		int32_t refreshRate;
		int32_t redBits;
		int32_t greenBits;
		int32_t blueBits;
		int32_t width;
		int32_t height;

	public:
		VideoMode(int32_t refreshRate, int32_t redBits, int32_t greenBits, int32_t blueBits, int32_t width, int32_t height);
		int32_t getRefreshRate();
		int32_t getRedBits();
		int32_t getGreenBits();
		int32_t getBlueBits();
		int32_t getWidth();
		int32_t getHeight();

	};

}

#endif
