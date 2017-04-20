#include "FontGlyph.h"

namespace librender
{

	FontGlyph::FontGlyph(uint16_t advance, uint16_t width, uint16_t height, int16_t offsetX, int16_t offsetY)
	: advance(advance)
	, height(height)
	, width(width)
	, offsetX(offsetX)
	, offsetY(offsetY)
	{
		//Empty
	}

}
