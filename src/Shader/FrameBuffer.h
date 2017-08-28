#ifndef LIBRENDER_FRAME_BUFFER_H
# define LIBRENDER_FRAME_BUFFER_H

# include "../GL.h"

namespace librender
{

	class FrameBuffer
	{

	private:
		GLuint id;

	public:
		FrameBuffer();
		~FrameBuffer();
		void bind();

	};

}

#endif
