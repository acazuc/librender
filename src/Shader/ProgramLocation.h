#ifndef LIBRENDER_PROGRAM_LOCATION_H
# define LIBRENDER_PROGRAM_LOCATION_H

# include "./VertexBuffer.h"
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
		void setVec2i(GLint val1, GLint val2);
		void setVec3i(GLint val1, GLint val2, GLint val3);
		void setVec4i(GLint val1, GLint val2, GLint val3, GLint val4);
		void setVec1f(GLfloat val);
		void setVec2f(GLfloat val1, GLfloat val2);
		void setVec2f(glm::vec2 &vec);
		void setVec3f(GLfloat val1, GLfloat val2, GLfloat val3);
		void setVec3f(glm::vec3 &vec);
		void setVec4f(GLfloat val1, GLfloat val2, GLfloat val3, GLfloat val4);
		void setVec4f(glm::vec4 &vec);
		void setMat3f(glm::mat3 &mat);
		void setMat4f(glm::mat4 &mat);
		void setVertexBuffer(VertexBuffer &buffer);
		void setVertexAttribArray(bool asArray);
		inline GLint getLocation() {return (this->location);};

	};

}

#endif
