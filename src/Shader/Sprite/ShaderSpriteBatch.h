#ifndef LIBRENDER_SHADER_SPRITE_BATCH_H
# define LIBRENDER_SHADER_SPRITE_BATCH_H

# include "./ShaderSpriteBatchEntry.h"
# include "../Program.h"
# include <vector>

namespace librender
{

	class ShaderSpriteBatch
	{

	private:
		std::vector<ShaderSpriteBatchEntry*> entries;
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
		uint32_t verticesNumber;
		uint8_t changes;
		float *texCoords;
		float *vertexes;
		float *colors;
		float x;
		float y;
		bool mustResize;
		void updateVerticesNumber();
		void updateTexCoords();
		void updateVertexes();
		void updateIndices();
		void updateColors();
		void resize();

	public:
		ShaderSpriteBatch();
		~ShaderSpriteBatch();
		void draw(Mat4 &viewProj);
		void addEntry(ShaderSpriteBatchEntry *entry);
		void removeEntry(ShaderSpriteBatchEntry *entry);
		inline void setTexCoordsLocation(ProgramLocation *location) {this->texCoordsLocation = location;};
		inline void setVertexesLocation(ProgramLocation *location) {this->vertexesLocation = location;};
		inline void setColorsLocation(ProgramLocation *location) {this->colorsLocation = location;};
		inline void setMvpLocation(ProgramLocation *location) {this->mvpLocation = location;};
		void setTexture(Texture *texture);
		inline Texture *getTexture() {return (this->texture);};
		inline void setProgram(Program *program) {this->program = program;};
		inline std::vector<ShaderSpriteBatchEntry*> &getEntries() {return (this->entries);};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void setX(float x) {this->x = x;};
		inline void setY(float y) {this->y = y;};
		inline void setMustResize(bool mustResize) {this->mustResize = mustResize;};

	};

}

#endif
