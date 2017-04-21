#ifndef LIBRENDER_FRAGMENT_SHADER_H
# define LIBRENDER_FRAGMENT_SHADER_H

# include "../GL.h"
# include <cstdlib>

namespace librender
{

	class FragmentShader
	{

	private:
		GLuint id;

	public:
		FragmentShader(const char *data, size_t len);
		~FragmentShader();
		inline GLuint getId() {return (this->id);};

	};

}

#endif
