#include "Context.h"

namespace librender
{

	Context::Context(Window *window)
	: window(window)
	, currentVertexArray(&this->defaultVertexArray)
	{
		for (uint32_t i = 0; i < CONTEXT_MAX_SAMPLERS; ++i)
		{
			samplers[i].mipmap = SAMPLER_MIPMAP_LINEAR;
			samplers[i].minFilter = SAMPLER_LINEAR;
			samplers[i].magFilter = SAMPLER_LINEAR;
			samplers[i].wrapS = SAMPLER_REPEAT;
			samplers[i].wrapT = SAMPLER_REPEAT;
			samplers[i].wrapR = SAMPLER_REPEAT;
			samplers[i].anisotropicLevel = 1;
		}
	}

	Context::~Context()
	{
	}

}
