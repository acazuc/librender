#ifndef LIBRENDER_SHADER_H
# define LIBRENDER_SHADER_H

# include "../GL.h"
# include <cstdlib>

namespace librender
{

	class Shader
	{

	protected:
		GLuint id;

	public:
		Shader(GLenum type, const char *data);
		~Shader();
		inline GLuint getId() {return (this->id);};
	
	};

}

#endif
