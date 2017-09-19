#ifndef LIBRENDER_SHADER_SPRITE_H
# define LIBRENDER_SHADER_SPRITE_H

# include "./ShaderSpriteEntry.h"
# include "../VertexBuffer.h"
# include "../../Texture.h"
# include "../Program.h"

namespace librender
{

	class ShaderSprite : public ShaderSpriteEntry
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
		Texture *texture;
		Program *program;

	public:
		ShaderSprite();
		~ShaderSprite();
		void draw(glm::mat4 &viewProj);
		inline void setTexCoordsLocation(ProgramLocation *location) {this->texCoordsLocation = location;};
		inline void setVertexesLocation(ProgramLocation *location) {this->vertexesLocation = location;};
		inline void setColorsLocation(ProgramLocation *location) {this->colorsLocation = location;};
		inline void setMvpLocation(ProgramLocation *location) {this->mvpLocation = location;};
		inline void setProgram(Program *program) {this->program = program;};
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return (this->texture);};

	};

}

#endif
