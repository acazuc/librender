#ifndef LIBRENDER_SHADER_TEXT_H
# define LIBRENDER_SHADER_TEXT_H

# include "./ShaderTextEntry.h"
# include "../../Font/Font.h"
# include "../Program.h"

namespace librender
{

	class ShaderText : public ShaderTextEntry
	{

	protected:
		ProgramLocation *texCoordsLocation;
		ProgramLocation *vertexesLocation;
		ProgramLocation *colorsLocation;
		ProgramLocation *mvpLocation;
		VertexBuffer texCoordsBuffer;
		VertexBuffer vertexesBuffer;
		VertexBuffer indicesBuffer;
		VertexBuffer colorsBuffer;
		Program *program;
		Font *font;
		uint32_t oldVerticesNumber;

	public:
		ShaderText();
		~ShaderText();
		void draw(Mat4 &viewProj);
		inline void setTexCoordsLocation(ProgramLocation *location) {this->texCoordsLocation = location;};
		inline void setVertexesLocation(ProgramLocation *location) {this->vertexesLocation = location;};
		inline void setColorsLocation(ProgramLocation *location) {this->colorsLocation = location;};
		inline void setMvpLocation(ProgramLocation *location) {this->mvpLocation = location;};
		inline void setProgram(Program *program) {this->program = program;};
		void setFont(Font *font);
		inline Font *getFont() {return (this->font);};

	};

}

#endif
