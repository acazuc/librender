#ifndef LIBRENDER_COLOR_H
# define LIBRENDER_COLOR_H

# include <GLFW/glfw3.h>

namespace librender
{

	class Color
	{

	private:
		float red;
		float green;
		float blue;
		float alpha;

	public:
		Color();
		Color(Color &color);
		Color(float red, float green, float blue, float alpha = 1);
		Color(float rgb, float alpha = 1);
		inline void set(float red, float green, float blue, float alpha = 1) {this->red = red;this->green = green;this->blue = blue;this->alpha = alpha;};
		inline void set(float rgb, float alpha = 1) {this->red = rgb;this->green = rgb;this->blue = rgb;this->alpha = alpha;};
		void bind() {glColor4f(this->red, this->green, this->blue, this->alpha);};
		void setRed(float red) {this->red = red;};
		float getRed() {return (this->red);};
		void setGreen(float green) {this->green = green;};
		float getGreen() {return (this->green);};
		void setBlue(float blue) {this->blue = blue;};
		float getBlue() {return (this->blue);};
		void setAlpha(float alpha) {this->alpha = alpha;};
		float getAlpha() {return (this->alpha);};
		inline Color &operator = (Color &color) {this->red = color.getRed();this->green = color.getGreen();this->blue = color.getBlue();this->alpha = color.getAlpha();return (*this);};
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

	};

}

#endif
