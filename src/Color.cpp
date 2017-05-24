#include "Color.h"

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
	Color Color::DARKBLUE(0, 0, .5f);
	Color Color::LIGHTYELLOW(1, 1, .33f);
	Color Color::YELLOW(1, 1, 0);
	Color Color::DARKYELLOW(.5f, .5f, 0);
	Color Color::LIGHTORANGE(1, .75f, .25f);
	Color Color::ORANGE(1, .5f, 0);
	Color Color::DARKORANGE(.5f, .25f, 0);

	Color::Color(Color &color)
	{
		this->red = color.red;
		this->green = color.green;
		this->blue = color.blue;
		this->alpha = color.alpha;
	}

	Color::Color(float red, float green, float blue, float alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	Color::Color(float rgb, float alpha)
	{
		this->red = rgb;
		this->green = rgb;
		this->blue = rgb;
		this->alpha = alpha;
	}

	bool Color::compare(Color &color)
	{
		return (this->red != color.getRed() || this->green != color.getGreen() || this->blue != color.getBlue() || this->alpha != color.getAlpha());
	}

	bool Color::compare(Color *color)
	{
		return (compare(*color));
	}

	Color &Color::operator += (float val)
	{
		this->red += val;
		this->green += val;
		this->blue += val;
		return (*this);
	}

	Color &Color::operator -= (float val)
	{
		this->red -= val;
		this->green -= val;
		this->blue -= val;
		return (*this);
	}

	Color &Color::operator = (Color &color)
	{
		this->red = color.red;
		this->green = color.green;
		this->blue = color.blue;
		this->alpha = color.alpha;
		return (*this);
	}

}
