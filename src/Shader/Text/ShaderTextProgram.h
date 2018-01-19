#ifndef SHADER_TEXT_PROGRAM_H
# define SHADER_TEXT_PROGRAM_H

# include "../Program.h"

namespace librender
{

	class ShaderTextProgram
	{

	public:
		ProgramLocation *texCoordsLocation;
		ProgramLocation *vertexesLocation;
		ProgramLocation *colorsLocation;
		ProgramLocation *mvpLocation;
		Program *program;
		ShaderTextProgram() : texCoordsLocation(NULL), vertexesLocation(NULL), colorsLocation(NULL), mvpLocation(NULL), program(NULL) {};

	};

}

#endif
