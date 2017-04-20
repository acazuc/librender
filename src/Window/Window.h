#ifndef LIBRENDER_WINDOW_H
# define LIBRENDER_WINDOW_H

# include "EventsManager.h"
# include "../GL.h"
# include <string>

namespace librender
{

	enum WindowCursor
	{
		WINDOW_CURSOR_HRESIZE,
		WINDOW_CURSOR_VRESIZE,
		WINDOW_CURSOR_ARROW,
		WINDOW_CURSOR_CROSS,
		WINDOW_CURSOR_IBEAM,
		WINDOW_CURSOR_HAND
	};

	class Window
	{

	private:
		EventsManager eventsManager;
		GLFWwindow *window;
		GLFWcursor *hResizeCursor;
		GLFWcursor *vResizeCursor;
		GLFWcursor *arrowCursor;
		GLFWcursor *crossCursor;
		GLFWcursor *ibeamCursor;
		GLFWcursor *handCursor;
		bool isFullscreen;
		bool focused;
		int currentCursor;
		int prevWidth;
		int prevHeight;
		int semiDiag;
		int mouseX;
		int mouseY;
		int width;
		int height;

	public:
		Window(std::string title, int width, int height);
		~Window();
		void enableFullscreen();
		void disableFullscreen();
		void switchFullscreen();
		void maximize();
		bool closeRequested();
		void setBorders(bool borders);
		void setResizable(bool resizable);
		void setVSync(bool vsync);
		void clearScreen();
		void update();
		void pollEvents();
		void resized(int width, int height);
		void updateGLContext();
		bool isButtonDown(int button);
		bool isKeyDown(int key);
		std::string getClipboard();
		void setClipboard(std::string text);
		void setIcon(char *data, uint32_t width, uint32_t height);
		void setHResizeCursor();
		void setVResizeCursor();
		void setArrowCursor();
		void setCrossCursor();
		void setIbeamCursor();
		void setHandCursor();
		void setCursor(enum WindowCursor cursor);
		void setFocused(bool focused);
		void setWindowResizedCallback(WindowResizedCallback callback);
		void setScrollCallback(ScrollCallback callback);
		void setMouseMoveCallback(MouseMoveCallback callback);
		void setMouseDownCallback(MouseDownCallback callback);
		void setMouseUpCallback(MouseUpCallback callback);
		void setKeyDownCallback(KeyDownCallback callback);
		void setKeyPressCallback(KeyPressCallback callback);
		void setKeyUpCallback(KeyUpCallback callback);
		void setCharCallback(CharCallback callback);
		inline EventsManager &getEventsManager() {return (this->eventsManager);};
		inline void setMouseX(int mouseX) {this->mouseX = mouseX;};
		inline void setMouseY(int mouseY) {this->mouseY = mouseY;};
		inline bool isFocused() {return (this->focused);};
		inline int getCurrentCursor() {return (this->currentCursor);};
		inline int getSemiDiag() {return (this->semiDiag);};
		inline int getMouseX() {return (this->mouseX);};
		inline int getMouseY() {return (this->mouseY);};
		inline int getHeight() {return (this->height);};
		inline int getWidth() {return (this->width);};

	};

}

#endif
