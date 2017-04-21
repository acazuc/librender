#ifndef LIBRENDER_VERTEX_SHADER_H
# define LIBRENDER_VERTEX_SHADER_H

# include "../GL.h"
# include <cstdlib>

namespace librender
{

	class VertexShader
	{

	private:
		GLuint id;

	public:
		VertexShader(const char *data, size_t len);
		~VertexShader();
		inline GLuint getId() {return (this->id);};

	};

}

#endif
