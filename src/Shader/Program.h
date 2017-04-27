#ifndef LIBRENDER_PROGRAM_H
# define LIBRENDER_PROGRAM_H

# include "FragmentShader.h"
# include "VertexShader.h"
# include "../GL.h"

namespace librender
{

	class Program
	{

	private:
		FragmentShader *fragmentShader;
		VertexShader *vertexShader;
		GLuint id;

	public:
		Program(FragmentShader *fragmentShader, VertexShader *vertexShader);
		~Program();
		GLuint getAttribLocation(const char *name);
		void use();

	};

}

#endif
