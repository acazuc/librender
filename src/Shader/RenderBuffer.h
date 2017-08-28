#ifndef LIBRENDER_RENDER_BUFFER_H
# define LIBRENDER_RENDER_BUFFER_H

# include "../GL.h"

namespace librender
{

	class RenderBuffer
	{

	private:
		GLuint id;

	public:
		RenderBuffer();
		~RenderBuffer();
		void bind();

	};

}

#endif
