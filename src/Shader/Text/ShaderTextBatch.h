#ifndef LIBRENDER_SHADER_TEXT_BATCH_H
# define LIBRENDER_SHADER_TEXT_BATCH_H

# include "./ShaderTextBatchEntry.h"
# include "../Program.h"
# include <vector>

namespace librender
{

	class ShaderTextBatch
	{

	private:
		std::vector<ShaderTextBatchEntry*> entries;
		ProgramLocation *texCoordsLocation;
		ProgramLocation *vertexesLocation;
		ProgramLocation *colorsLocation;
		ProgramLocation *mvpLocation;
		VertexBuffer texCoordsBuffer;
		VertexBuffer vertexesBuffer;
		VertexBuffer indicesBuffer;
		VertexBuffer colorsBuffer;
		Program *program;
		Vec2 *texCoords;
		Vec2 *vertexes;
		Vec4 *colors;
		Font *font;
		Vec2 pos;
		uint32_t verticesNumber;
		uint8_t changes;
		bool mustResize;
		void updateVerticesNumber();
		void updateTexCoords();
		void updateVertexes();
		void updateIndices();
		void updateColors();
		void resize();

	public:
		ShaderTextBatch();
		~ShaderTextBatch();
		void draw(Mat4 &viewProj);
		void addEntry(ShaderTextBatchEntry *entry);
		void removeEntry(ShaderTextBatchEntry *entry);
		void clearEntries();
		void setFont(Font *font);
		inline Font *getFont() {return (this->font);};
		inline void setTexCoordsLocation(ProgramLocation *location) {this->texCoordsLocation = location;};
		inline void setVertexesLocation(ProgramLocation *location) {this->vertexesLocation = location;};
		inline void setColorsLocation(ProgramLocation *location) {this->colorsLocation = location;};
		inline void setMvpLocation(ProgramLocation *location) {this->mvpLocation = location;};
		inline void setProgram(Program *program) {this->program = program;};
		inline void addChanges(uint8_t changes) {this->changes |= changes;};
		inline void setPos(float x, float y) {setX(x);setY(y);};
		inline void setX(float x) {this->pos.x = x;};
		inline void setY(float y) {this->pos.y = y;};
		inline void setMustResize(bool mustResize) {this->mustResize = mustResize;};

	};

}

#endif
