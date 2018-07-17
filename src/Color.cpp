#include "Color.h"
#include "GL.h"

namespace librender
{

	Color Color::WHITE(1, 1, 1);
	Color Color::LIGHTGREY(.75f, .75f, .75f);
	Color Color::GREY(.5f, .5f, .5f);
	Color Color::DARKGREY(.25f, .25f, .25f);
	Color Color::BLACK(0, 0, 0);
	Color Color::LIGHTRED(1, .25f, .25f);
	Color Color::RED(1, 0, 0);
	Color Color::DARKRED(.5f, 0, 0);
	Color Color::LIGHTGREEN(.25f, 1, .25f);
	Color Color::GREEN(0, 1, 0);
	Color Color::DARKGREEN(0, .5f, 0);
	Color Color::LIGHTBLUE(.25f, 1, 1);
	Color Color::BLUE(0, 0, 1);
	Color Color::DARKBLUE(0, 0, .5);
	Color Color::LIGHTYELLOW(1, 1, .33);
	Color Color::YELLOW(1, 1, 0);
	Color Color::DARKYELLOW(.5, .5, 0);
	Color Color::LIGHTORANGE(1, .75, .25);
	Color Color::ORANGE(1, .5, 0);
	Color Color::DARKORANGE(.5, .25, 0);
	Color Color::PURPLE(.75, 0, .75);
	Color Color::DARKPURPLE(.5, 0, .5);
	Color Color::LIGHTPURPLE(1, 0, 1);

	Color::Color(Color &color)
	: Vec4(color.r, color.g, color.b, color.a)
	{
		//Empty
	}

	Color::Color(float r, float g, float b, float a)
	: Vec4(r, g, b, a)
	{
		//Empty
	}

	Color::Color(float rgb, float a)
	: Vec4(rgb, a)
	{
		//Empty
	}
	
	void Color::bind()
	{
		glColor4f(this->r, this->g, this->b, this->a);
	}

	bool Color::compare(Color &color)
	{
		return this->r != color.r || this->g != color.g || this->b != color.b || this->a != color.a;
	}

	bool Color::compare(Color *color)
	{
		return compare(*color);
	}

	Color &Color::operator += (float val)
	{
		this->r += val;
		this->g += val;
		this->b += val;
		return *this;
	}

	Color &Color::operator -= (float val)
	{
		this->r -= val;
		this->g -= val;
		this->b -= val;
		return *this;
	}

}
