#include "ShaderSprite.h"
#include "./ShaderSpriteUpdate.h"
#include "../../GL.h"

namespace librender
{

	ShaderSprite::ShaderSprite()
	: ShaderSpriteEntry()
	, texCoordsLocation(NULL)
	, vertexesLocation(NULL)
	, colorsLocation(NULL)
	, mvpLocation(NULL)
	, texture(NULL)
	, program(NULL)
	{
		GLuint indices[] = {0, 3, 1, 2, 1, 3};
		this->indicesBuffer.setData(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), GL_UNSIGNED_INT, 1, GL_STATIC_DRAW);
	}

	ShaderSprite::~ShaderSprite()
	{
		//Empty
	}

	void ShaderSprite::draw(Mat4 &viewProj)
	{
		if (!this->texture || !this->program || !this->texCoordsLocation || !this->vertexesLocation || !this->colorsLocation || !this->mvpLocation)
			return;
		uint8_t changes = this->updatesRequired;
		update();
		if (changes & SHADER_SPRITE_UPDATE_TEX_COORDS)
			this->texCoordsBuffer.setData(GL_ARRAY_BUFFER, this->texCoords, sizeof(*this->texCoords) * this->verticesNumber, GL_FLOAT, 2, GL_DYNAMIC_DRAW);
		if (changes & SHADER_SPRITE_UPDATE_VERTEXES)
			this->vertexesBuffer.setData(GL_ARRAY_BUFFER, this->vertexes, sizeof(*this->vertexes) * this->verticesNumber, GL_FLOAT, 2, GL_DYNAMIC_DRAW);
		if (changes & SHADER_SPRITE_UPDATE_COLORS)
			this->colorsBuffer.setData(GL_ARRAY_BUFFER, this->colors, sizeof(*this->colors) * this->verticesNumber, GL_FLOAT, 4, GL_DYNAMIC_DRAW);
		this->texture->bind();
		this->program->use();
		this->texCoordsLocation->setVertexBuffer(this->texCoordsBuffer);
		this->vertexesLocation->setVertexBuffer(this->vertexesBuffer);
		this->colorsLocation->setVertexBuffer(this->colorsBuffer);
		this->indicesBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
		Mat4 model(Mat4::translate(Mat4(1), Vec3(this->pos, 0)));
		Mat4 mvp(viewProj * model);
		this->mvpLocation->setMat4f(mvp);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

	void ShaderSprite::setTexture(Texture *texture)
	{
		if (this->texture == texture)
			return;
		this->texture = texture;
		this->updatesRequired |= SHADER_SPRITE_UPDATE_VERTEXES;
		this->updatesRequired |= SHADER_SPRITE_UPDATE_TEX_COORDS;
	}

}
