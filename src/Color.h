#ifndef LIBRENDER_COLOR_H
# define LIBRENDER_COLOR_H

# include "Vec/Vec4.h"

namespace librender
{

	class Color : public Vec4
	{

	public:
		Color(Color &color);
		Color(float r, float g, float b, float a = 1);
		Color(float rgb, float a = 1);
		inline void set(float r, float g, float b, float a = 1) {this->r = r;this->g = g;this->b = b;this->a = a;};
		inline void set(float rgb, float a = 1) {this->r = rgb;this->g = rgb;this->b = rgb;this->a = a;};
		bool compare(Color &color);
		bool compare(Color *color);
		void bind();
		Color &operator += (float val);
		Color &operator -= (float val);
		Color &operator = (Color &color);
		static Color WHITE;
		static Color LIGHTGREY;
		static Color GREY;
		static Color DARKGREY;
		static Color BLACK;
		static Color LIGHTRED;
		static Color RED;
		static Color DARKRED;
		static Color LIGHTGREEN;
		static Color GREEN;
		static Color DARKGREEN;
		static Color LIGHTBLUE;
		static Color BLUE;
		static Color DARKBLUE;
		static Color LIGHTYELLOW;
		static Color YELLOW;
		static Color DARKYELLOW;
		static Color LIGHTORANGE;
		static Color ORANGE;
		static Color DARKORANGE;
		static Color PURPLE;
		static Color DARKPURPLE;
		static Color LIGHTPURPLE;

	};

}

#endif
