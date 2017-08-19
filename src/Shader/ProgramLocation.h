#ifndef LIBRENDER_PROGRAM_LOCATION_H
# define LIBRENDER_PROGRAM_LOCATION_H

# include "./DataBuffer.h"
# include "../GL.h"
# include <glm/glm.hpp>

namespace librender
{

	class ProgramLocation
	{

	private:
		GLint location;

	public:
		ProgramLocation(GLint location);
		void setVec1i(GLint val);
		void setVec1f(GLfloat val);
		void setVec2f(glm::vec2 &vec);
		void setVec3f(glm::vec3 &vec);
		void setVec4f(glm::vec4 &vec);
		void setMat3f(glm::mat3 &mat);
		void setMat4f(glm::mat4 &mat);
		void setDataBuffer(DataBuffer &buffer);
		void setVertexAttribArray(bool asArray);
		inline GLint getLocation() {return (this->location);};

	};

}

#endif
