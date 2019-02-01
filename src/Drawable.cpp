#include "Drawable.h"
#include "./DrawableBuffers.h"
#include "./GL.h"

namespace librender
{

	Drawable::Drawable(Context &context)
	: context(context)
	, buffersChanged(0)
	, shapeType(GL_TRIANGLES)
	, initialized(false)
	{
	}

	Drawable::~Drawable()
	{
		if (this->initialized)
		{
			this->context.deleteVertexArray(&this->vertexArray);
			if (this->buffers & DRAWABLE_BUFFER_VERTEXES)
				this->context.deleteBuffer(&this->vertexes);
			if (this->buffers & DRAWABLE_BUFFER_TEX_COORDS)
				this->context.deleteBuffer(&this->texCoords);
			if (this->buffers & DRAWABLE_BUFFER_INDICES)
				this->context.deleteBuffer(&this->indices);
			if (this->buffers & DRAWABLE_BUFFER_COLORS)
				this->context.deleteBuffer(&this->colors);
		}
	}

	void Drawable::draw()
	{
		if (!this->initialized)
		{
			this->context.createVertexArray(&this->vertexArray);
			this->context.bindVertexArray(&this->vertexArray);
			if (this->buffers & DRAWABLE_BUFFER_VERTEXES)
			{
				this->context.createVertexBuffer(&this->vertexes);
				this->context.setAttrib(1, VERTEX_ATTRIB_FLOAT, 2, 0, 0);
				this->context.setAttribBuffer(1, &this->vertexes);
			}
			if (this->buffers & DRAWABLE_BUFFER_COLORS)
			{
				this->context.createVertexBuffer(&this->colors);
				this->context.setAttrib(2, VERTEX_ATTRIB_FLOAT, 4, 0, 0);
				this->context.setAttribBuffer(2, &this->colors);
			}
			if (this->buffers & DRAWABLE_BUFFER_TEX_COORDS)
			{
				this->context.createVertexBuffer(&this->texCoords);
				this->context.setAttrib(5, VERTEX_ATTRIB_FLOAT, 2, 0, 0);
				this->context.setAttribBuffer(5, &this->texCoords);
			}
			if (this->buffers & DRAWABLE_BUFFER_INDICES)
			{
				this->context.createIndiceBuffer(&this->indices);
				this->context.setIndexAttribType(VERTEX_ATTRIB_UNSIGNED_INT);
				this->context.setIndexAttribBuffer(&this->indices);
			}
			this->initialized = true;
		}
		else
		{
			this->context.bindVertexArray(&this->vertexArray);
		}
		if (this->buffersChanged & DRAWABLE_BUFFER_VERTEXES)
		{
			std::vector<Vec2> vertexes;
			vertexes.resize(getVerticesNumber());
			fillVertexes(vertexes.begin());
			this->context.updateBuffer(&this->vertexes, vertexes.data(), vertexes.size() * sizeof(*vertexes.data()));
		}
		if (this->buffersChanged & DRAWABLE_BUFFER_COLORS)
		{
			std::vector<Vec4> colors;
			colors.resize(getVerticesNumber());
			fillColors(colors.begin());
			this->context.updateBuffer(&this->colors, colors.data(), colors.size() * sizeof(*colors.data()));
		}
		if (this->buffersChanged & DRAWABLE_BUFFER_TEX_COORDS)
		{
			std::vector<Vec2> texCoords;
			texCoords.resize(getVerticesNumber());
			fillTexCoords(texCoords.begin());
			this->context.updateBuffer(&this->texCoords, texCoords.data(), texCoords.size() * sizeof(*texCoords.data()));
		}
		if (this->buffersChanged & DRAWABLE_BUFFER_INDICES)
		{
			std::vector<uint32_t> indices;
			indices.resize(getIndicesNumber());
			fillIndices(indices.begin());
			this->context.updateBuffer(&this->indices, indices.data(), indices.size() * sizeof(*indices.data()));
		}
		glPushMatrix();
		glTranslatef(this->pos.x, this->pos.y, 0);
		glScalef(this->scale.x, this->scale.y, 0);
		this->context.drawIndexed(PRIMITIVE_TRIANGLE, getIndicesNumber());
		glPopMatrix();
		this->buffersChanged = 0;
		this->context.bindVertexArray(nullptr);
	}

	void Drawable::requireUpdates(uint8_t updates)
	{
		this->buffersChanged |= this->buffers & updates;
		DrawableBase::requireUpdates(updates);
	}

}
