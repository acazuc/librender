#ifndef LIBRENDER_EVENTS_H
# define LIBRENDER_EVENTS_H

namespace librender
{

	typedef struct SKeyEvent
	{
		int key;
		int scancode;
		int mods;
	} KeyEvent;

	typedef struct SCharEvent
	{
		char *charcode;
	} CharEvent;

	typedef struct SMouseEvent
	{
		int button;
		int mods;
	} MouseEvent;

	typedef struct SScrollEvent
	{
		int scroll;
	} ScrollEvent;

}

#endif
