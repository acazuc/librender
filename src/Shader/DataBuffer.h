#ifndef LIBRENDER_DATA_BUFFER_H
# define LIBRENDER_DATA_BUFFER_H

# include "../GL.h"

namespace librender
{

	class DataBuffer
	{

	private:
		GLsizei stride;
		GLenum type;
		GLuint id;
		GLint size;

	public:
		DataBuffer();
		~DataBuffer();
		void setData(GLenum bufType, const void *data, GLsizei size, GLenum type, GLsizei stride, GLenum usage);
		void bind(GLenum type);
		inline GLsizei getStride() {return (this->stride);};
		inline GLenum getType() {return (this->type);};
		inline GLint getSize() {return (this->size);};

	};

}

#endif
