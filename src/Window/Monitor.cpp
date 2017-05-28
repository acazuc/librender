#include "Monitor.h"

namespace librender
{

	Monitor::Monitor(GLFWmonitor *handle)
	: handle(handle)
	{
		glfwGetMonitorPhysicalSize(this->handle, &this->width, &this->height);
		this->name = glfwGetMonitorName(this->handle);
		int videoModesCount = 0;
		const GLFWvidmode *videoModes = glfwGetVideoModes(this->handle, &videoModesCount);
		this->videoModes = new VideoMode*[videoModesCount + 1];
		for (int i = 0; i < videoModesCount; ++i)
		{
			const GLFWvidmode &videoMode = videoModes[i];
			this->videoModes[i] = new VideoMode(videoMode.refreshRate, videoMode.redBits, videoMode.greenBits, videoMode.blueBits, videoMode.width, videoMode.height);
		}
		this->videoModes[videoModesCount] = NULL;
	}

	VideoMode **Monitor::getVideoModes()
	{
		return (this->videoModes);
	}

	std::string Monitor::getName()
	{
		return (this->name);
	}

	int32_t Monitor::getWidth()
	{
		return (this->width);
	}

	int32_t Monitor::getHeight()
	{
		return (this->height);
	}

}
