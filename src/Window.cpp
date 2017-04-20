#include "Window.h"
#include "EventsListener.h"
#include <cstring>
#include <utf8.h>
#include <cmath>

namespace librender
{

	Window::Window(std::string title, int width, int height)
	{
		this->mouseX = 0;
		this->mouseY = 0;
		glfwSetErrorCallback(EventsListener::glfwErrorListener);
		this->width = width;
		this->height = height;
		this->focused = true;
		this->semiDiag = std::sqrt(std::pow(this->width, 2) + std::pow(this->height, 2));
		this->isFullscreen = false;
		if (!(this->window = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL)))
		{
			std::cerr << "Failed to create window" << std::endl;
			exit(EXIT_FAILURE);
		}
		glfwSetWindowUserPointer(this->window, this);
		glfwMakeContextCurrent(this->window);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0, 0, 0, 1);
		this->currentCursor = GLFW_ARROW_CURSOR;
		this->hResizeCursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		this->vResizeCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		this->arrowCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		this->crossCursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		this->ibeamCursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		this->handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		glfwSetCharCallback(this->window, EventsListener::charListener);
		glfwSetKeyCallback(this->window, EventsListener::keyListener);
		glfwSetScrollCallback(this->window, EventsListener::scrollListener);
		glfwSetMouseButtonCallback(this->window, EventsListener::mouseListener);
		glfwSetCursorPosCallback(this->window, EventsListener::cursorListener);
		glfwSetFramebufferSizeCallback(this->window, EventsListener::windowResizeListener);
		glfwSetWindowFocusCallback(this->window, EventsListener::windowFocusListener);
		updateGLContext();
		int count = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		for (int i = 0; i < count; ++i)
		{
			int mWidth = 0;
			int mHeight = 0;
			glfwGetMonitorPhysicalSize(monitors[i], &mWidth, &mHeight);
			std::cout << glfwGetMonitorName(monitors[i]) << " (" << mWidth << "x" << mHeight << ") :" << std::endl;
			int modesCount = 0;
			const GLFWvidmode *modes = glfwGetVideoModes(monitors[i], &modesCount);
			for (int j = 0; j < modesCount; ++j)
			{
				std::cout << "width: " << modes[j].width << ", height: " << modes[j].height << ", redBits: " << modes[j].redBits << ", greenBits: " << modes[j].greenBits << ", blueBits: " << modes[j].blueBits << ", refreshRate: " << modes[j].refreshRate << std::endl;
			}
			std::cout << std::endl;
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(this->window);
	}

	void Window::setIcon(char *data, uint32_t width, uint32_t height)
	{
		GLFWimage img = {static_cast<int>(width), static_cast<int>(height), reinterpret_cast<unsigned char*>(data)};
		glfwSetWindowIcon(this->window, 1, &img);
	}

	void Window::enableFullscreen()
	{
		if (!this->isFullscreen)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			this->isFullscreen = true;
			this->prevWidth = this->width;
			this->prevHeight = this->height;
			glfwSetWindowMonitor(this->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
	}

	void Window::disableFullscreen()
	{
		if (this->isFullscreen)
		{
			setBorders(true);
			glfwSetWindowMonitor(window, NULL, 0, 0, this->prevWidth, this->prevHeight, GLFW_DONT_CARE);
			this->isFullscreen = false;
		}
	}

	void Window::switchFullscreen()
	{
		if (this->isFullscreen)
			disableFullscreen();
		else
			enableFullscreen();
	}

	void Window::maximize()
	{
		glfwMaximizeWindow(this->window);
	}

	void Window::resized(int width, int height)
	{
		this->semiDiag = std::sqrt(std::pow(width, 2) + std::pow(height, 2)) / 2;
		this->width = width;
		this->height = height;
		updateGLContext();
	}

	void Window::updateGLContext()
	{
		glViewport(0, 0, this->width, this->height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, this->width, this->height, 0, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	bool Window::isButtonDown(int button)
	{
		return (glfwGetMouseButton(this->window, button) == GLFW_PRESS);
	}

	bool Window::isKeyDown(int key)
	{
		return (glfwGetKey(this->window, key) == GLFW_PRESS);
	}

	std::string Window::getClipboard()
	{
		std::string str = glfwGetClipboardString(this->window);
		if (!utf8::is_valid(str.begin(), str.end()))
		{
			std::string tmp;
			utf8::replace_invalid(str.begin(), str.end(), back_inserter(tmp));
			str = tmp;
		}
		return (str);
	}

	void Window::setClipboard(std::string str)
	{
		glfwSetClipboardString(this->window, str.c_str());
	}

	bool Window::closeRequested()
	{
		return (glfwWindowShouldClose(this->window));
	}

	void Window::setBorders(bool borders)
	{
		glfwWindowHint(GLFW_DECORATED, borders ? GL_TRUE : GL_FALSE);
	}

	void Window::setResizable(bool resizable)
	{
		glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
	}

	void Window::setVSync(bool vsync)
	{
		glfwSwapInterval(vsync ? 1 : 0);
	}

	void Window::clearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		glfwSwapBuffers(this->window);
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	void Window::setHResizeCursor()
	{
		if (this->currentCursor != GLFW_HRESIZE_CURSOR)
		{
			this->currentCursor = GLFW_HRESIZE_CURSOR;
			glfwSetCursor(this->window, this->hResizeCursor);
		}
	}

	void Window::setVResizeCursor()
	{
		if (this->currentCursor != GLFW_VRESIZE_CURSOR)
		{
			this->currentCursor = GLFW_VRESIZE_CURSOR;
			glfwSetCursor(window, this->vResizeCursor);
		}
	}

	void Window::setArrowCursor()
	{
		if (this->currentCursor != GLFW_ARROW_CURSOR)
		{
			this->currentCursor = GLFW_ARROW_CURSOR;
			glfwSetCursor(window, this->arrowCursor);
		}
	}

	void Window::setCrossCursor()
	{
		if (this->currentCursor != GLFW_CROSSHAIR_CURSOR)
		{
			this->currentCursor = GLFW_CROSSHAIR_CURSOR;
			glfwSetCursor(window, this->crossCursor);
		}
	}

	void Window::setIbeamCursor()
	{
		if (this->currentCursor != GLFW_IBEAM_CURSOR)
		{
			this->currentCursor = GLFW_IBEAM_CURSOR;
			glfwSetCursor(window, this->ibeamCursor);
		}
	}

	void Window::setHandCursor()
	{
		if (this->currentCursor != GLFW_HAND_CURSOR)
		{
			this->currentCursor = GLFW_HAND_CURSOR;
			glfwSetCursor(window, this->handCursor);
		}
	}

	void Window::setCursor(enum WindowCursor cursor)
	{
		switch (cursor)
		{
			case WINDOW_CURSOR_HRESIZE:
				setHResizeCursor();
				break;
			case WINDOW_CURSOR_VRESIZE:
				setVResizeCursor();
				break;
			case WINDOW_CURSOR_ARROW:
				setArrowCursor();
				break;
			case WINDOW_CURSOR_CROSS:
				setCrossCursor();
				break;
			case WINDOW_CURSOR_IBEAM:
				setIbeamCursor();
				break;
			case WINDOW_CURSOR_HAND:
				setHandCursor();
				break;
		}
	}

	void Window::setFocused(bool focused)
	{
		this->focused = focused;
	}

}
