#ifndef LIBRENDER_MONITOR_H
# define LIBRENDER_MONITOR_H

# include "VideoMode.h"
# include "../GL.h"
# include <cstdint>
# include <string>

namespace librender
{

	class Monitor
	{

	private:
		GLFWmonitor *handle;
		VideoMode **videoModes;
		std::string name;
		int32_t width;
		int32_t height;

	public:
		Monitor(GLFWmonitor *handle);
		VideoMode **getVideoModes();
		std::string getName();
		int32_t getWidth();
		int32_t getHeight();

	};

}

#endif
