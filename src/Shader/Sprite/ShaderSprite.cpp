#include "ShaderSprite.h"
#include "./ShaderSpriteUpdate.h"
#include "../../GL.h"

namespace librender
{

	ShaderSprite::ShaderSprite()
	: texture(nullptr)
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
		uint8_t changes = this->updatesRequired;
		update();
		if (changes & SHADER_SPRITE_UPDATE_TEX_COORDS)
			this->texCoordsBuffer.setData(GL_ARRAY_BUFFER, this->texCoords.data(), sizeof(*this->texCoords.data()) * this->verticesNumber, GL_FLOAT, 2, GL_DYNAMIC_DRAW);
		if (changes & SHADER_SPRITE_UPDATE_VERTEXES)
			this->vertexesBuffer.setData(GL_ARRAY_BUFFER, this->vertexes.data(), sizeof(*this->vertexes.data()) * this->verticesNumber, GL_FLOAT, 2, GL_DYNAMIC_DRAW);
		if (changes & SHADER_SPRITE_UPDATE_COLORS)
			this->colorsBuffer.setData(GL_ARRAY_BUFFER, this->colors.data(), sizeof(*this->colors.data()) * this->verticesNumber, GL_FLOAT, 4, GL_DYNAMIC_DRAW);
		if (this->texture)
			this->texture->bind();
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		this->program.program->use();
		if (this->program.texCoordsLocation)
			this->program.texCoordsLocation->setVertexBuffer(this->texCoordsBuffer);
		if (this->program.vertexesLocation)
			this->program.vertexesLocation->setVertexBuffer(this->vertexesBuffer);
		if (this->program.colorsLocation)
			this->program.colorsLocation->setVertexBuffer(this->colorsBuffer);
		this->indicesBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
		if (this->program.mvpLocation)
		{
			Mat4 model(Mat4::translate(Mat4(1), Vec3(this->pos, 0)));
			Mat4 mvp(viewProj * model);
			this->program.mvpLocation->setMat4f(mvp);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
