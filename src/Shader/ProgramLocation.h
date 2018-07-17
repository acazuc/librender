#ifndef LIBRENDER_PROGRAM_LOCATION_H
# define LIBRENDER_PROGRAM_LOCATION_H

# include "../Mat/Mat4.h"
# include "../Mat/Mat3.h"
# include "../Vec/Vec4.h"
# include "../Vec/Vec3.h"
# include "../Vec/Vec2.h"
# include "./VertexBuffer.h"
# include "../GL.h"

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
		void setVec2f(Vec2 &vec);
		void setVec3f(GLfloat val1, GLfloat val2, GLfloat val3);
		void setVec3f(Vec3 &vec);
		void setVec4f(GLfloat val1, GLfloat val2, GLfloat val3, GLfloat val4);
		void setVec4f(Vec4 &vec);
		void setMat3f(Mat3 &mat);
		void setMat4f(Mat4 &mat);
		void setVertexBuffer(VertexBuffer &buffer);
		void setVertexAttribArray(bool asArray);
		inline GLint getLocation() {return this->location;};

	};

}

#endif
