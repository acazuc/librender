#ifndef LIBRENDER_EVENTS_LISTENER_H
# define LIBRENDER_EVENTS_LISTENER_H

# include <GLFW/glfw3.h>
# include "Events.h"


namespace librender
{

	typedef void (*MouseScrollCallback)(ScrollEvent &event);
	typedef void (*MouseMoveCallback)();
	typedef void (*MouseDownCallback)(MouseEvent &event);
	typedef void (*MouseUpCallback)(MouseEvent &event);
	typedef void (*KeyDownCallback)(KeyEvent &event);
	typedef void (*KeyPressCallback)(CharEvent &event);
	typedef void (*KeyUpCallback)(KeyEvent &event);

	class EventsListener
	{

	private:
		MouseScrollCallback mouseScrollCallback;
		MouseMoveCallback mouseMoveCallback;
		MouseDownCallback mouseDownCallback;
		MouseUpCallback mouseUpCallback;
		KeyDownCallback keyDownCallback;
		KeyPressCallback keyPressCallback;
		KeyUpCallback keyUpCallback;

	public:
		EventsListener();
		void charListener(GLFWwindow *window, unsigned int codepoint);
		void keyListener(GLFWwindow *window, int key, int scancode, int action, int mods);
		void scrollListener(GLFWwindow *window, double xoffset, double yoffset);
		void mouseListener(GLFWwindow *window, int button, int action, int mods);
		void cursorListener(GLFWwindow *window, double x, double y);
		void windowResizeListener(GLFWwindow *window, int width, int height);
		void glfwErrorListener(int error, const char *desc);
		void windowFocusListener(GLFWwindow *window, int focused);

	};

}

#endif
