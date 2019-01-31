#include "Context.h"

namespace librender
{

	Context::Context(Window *window)
	: window(window)
	, currentVertexArray(&this->defaultVertexArray)
	{
	}

	Context::~Context()
	{
	}

}
