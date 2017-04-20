#include "EventsListener.h"
#include "Events/Events.h"
#include "Utils/System.h"
#include "Window.h"
#include <vector>
#include <utf8.h>

namespace librender
{

	void EventsListener::EventsListener()
	{
		mouseScrollCallback = NULL;
		mouseMoveCallback = NULL;
		mouseDownCallback = NULL;
		mouseUpCallback = NULL;
		keyDownCallback = NULL;
		keyPressCallback = NULL;
		keyUpCallback = NULL;
	}

	void EventsListener::charListener(GLFWwindow* window, unsigned int codepoint)
	{
		if (!keyPressCallback)
			return;
		try
		{
			int utf32string[] = {static_cast<int>(codepoint), 0};
			std::string result;
			utf8::utf32to8(utf32string, &utf32string[1], std::back_inserter(result));
			CharEvent event;
			event.charcode = const_cast<char*>(result.c_str());
			reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->keyPress(event);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		(void)window;
	}

	void EventsListener::keyListener(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		try
		{
			if (!Main::getScreen())
				return;
			if (action == GLFW_PRESS || action == GLFW_RELEASE)
			{
				KeyEvent event;
				event.key = key;
				event.scancode = scancode;
				if (action == GLFW_PRESS)
					reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->keyDown(event);
				else if (action == GLFW_RELEASE)
					reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->keyUp(event);
			}
			if ((action == GLFW_REPEAT || action == GLFW_PRESS) && (key == GLFW_KEY_BACKSPACE || key == GLFW_KEY_DELETE || key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN))
			{
				char code[2];
				code[1] = 0;
				if (key == GLFW_KEY_BACKSPACE)
					code[0] = 0x08;
				else if (key == GLFW_KEY_DELETE)
					code[0] = 0x7F;
				else if (key == GLFW_KEY_LEFT)
					code[0] = 0x11;
				else if (key == GLFW_KEY_RIGHT)
					code[0] = 0x12;
				else if (key == GLFW_KEY_UP)
					code[0] = 0x13;
				else if (key == GLFW_KEY_DOWN)
					code[0] = 0x14;
				CharEvent event;
				event.charcode = code;
				Main::getScreen()->keyPress(event);
			}
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		(void)window;
		(void)scancode;
		(void)mods;
	}

	void EventsListener::scrollListener(GLFWwindow* window, double xoffset, double yoffset)
	{
		if (!yoffset)
			return ;
		if (!Main::getScreen())
			return;
		ScrollEvent event;
		event.scroll = yoffset;
		Main::getScreen()->mouseScroll(event);
		(void)xoffset;
		(void)window;
	}

	void EventsListener::mouseListener(GLFWwindow* window, int button, int action, int mods)
	{
		if (!Main::getScreen())
			return;
		MouseEvent event;
		event.button = button;
		event.mods = mods;
		if (action == GLFW_PRESS)
			Main::getScreen()->mouseDown(event);
		else if (action == GLFW_RELEASE)
			Main::getScreen()->mouseUp(event);
		(void)window;
		(void)mods;
	}

	void EventsListener::cursorListener(GLFWwindow* window, double x, double y)
	{
		Main::getWindow()->setMouseX(x);
		Main::getWindow()->setMouseY(y);
		if (!Main::getScreen())
			return;
		Main::getScreen()->mouseMove();
		(void)window;
	}

	void EventsListener::windowResizeListener(GLFWwindow *window, int width, int height)
	{
		Main::getWindow()->resized(width, height);
		if (!Main::getScreen())
			return;
		Main::getScreen()->windowResized();
		(void)window;
	}

	void EventsListener::glfwErrorListener(int error, const char *desc)
	{
		std::cerr << "GLFW Error: " << desc << "(" << error << ")" << std::endl;
	}

	void EventsListener::windowFocusListener(GLFWwindow *window, int focused)
	{
		Main::getWindow()->setFocused(focused == GLFW_TRUE);
		(void)window;
	}

}
