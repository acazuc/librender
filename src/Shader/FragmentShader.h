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
		FragmentShader(const char *data);
		~FragmentShader();
		inline GLuint getId() {return (this->id);};

	};

}

#endif
