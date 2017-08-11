#ifndef LIBRENDER_DATA_BUFFER_H
# define LIBRENDER_DATA_BUFFER_H

# include "../GL.h"

namespace librender
{

	class DataBuffer
	{

	private:
		GLuint id;

	public:
		DataBuffer();
		~DataBuffer();
		void setData(const void *data, uint64_t len, GLenum usage);
		void bind();

	};

}

#endif
