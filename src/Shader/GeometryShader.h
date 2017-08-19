#ifndef LIBRENDER_GEOMETRY_SHADER_H
# define LIBRENDER_GEOMETRY_SHADER_H

# include "../GL.h"
# include <cstdlib>

namespace librender
{

	class GeometryShader
	{

	private:
		GLuint id;

	public:
		GeometryShader(const char *data);
		~GeometryShader();
		inline GLuint getId() {return (this->id);};

	};

}

#endif
