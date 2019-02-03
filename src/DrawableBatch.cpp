#include "DrawableBatch.h"
#include "./DrawableBuffers.h"

namespace librender
{

	DrawableBatch::DrawableBatch(Context &context)
	: Drawable(context)
	, dirtyVertices(false)
	, dirtyIndices(false)
	{
	}

	DrawableBatch::~DrawableBatch()
	{
		for (size_t i = 0; i < this->childs.size(); ++i)
			this->childs[i]->setParent(nullptr);
	}

	void DrawableBatch::fillTexCoords(std::vector<Vec2>::iterator texCoords)
	{
		size_t count = 0;
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			DrawableBatched *child = this->childs[i];
			if (this->dirtyVertices || child->getChanges() & DRAWABLE_BUFFER_TEX_COORDS)
			{
				child->fillTexCoords(texCoords + count);
				child->removeChanges(DRAWABLE_BUFFER_TEX_COORDS);
			}
			count += child->getVerticesNumber();
		}
	}

	void DrawableBatch::fillVertexes(std::vector<Vec2>::iterator vertexes)
	{
		size_t count = 0;
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			DrawableBatched *child = this->childs[i];
			if (this->dirtyVertices || child->getChanges() & DRAWABLE_BUFFER_VERTEXES)
			{
				child->fillVertexes(vertexes + count);
				child->removeChanges(DRAWABLE_BUFFER_VERTEXES);
				float x = child->getX() - this->getX();
				float y = child->getY() - this->getY();
				Vec2 pos(child->getX() - getX(), child->getY() - getY());
				Vec2 scale(child->getScaleX(), child->getScaleY());
				if (pos.x || pos.y || scale.x != 1 || scale.y != 1)
				{
					for (size_t i = count; i < count + child->getVerticesNumber(); ++i)
					{
						vertexes[i] *= scale;
						vertexes[i] += pos;
					}
				}
			}
			count += child->getVerticesNumber();
		}
	}

	void DrawableBatch::fillIndices(std::vector<uint32_t>::iterator indices)
	{
		size_t count = 0;
		size_t offset = 0;
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			DrawableBatched *child = this->childs[i];
			if (this->dirtyIndices || child->getChanges() & DRAWABLE_BUFFER_INDICES)
			{
				child->fillIndices(indices + count);
				child->removeChanges(DRAWABLE_BUFFER_INDICES);
				for (size_t i = count; i < count + child->getIndicesNumber(); ++i)
					indices[i] += offset;
			}
			offset += child->getVerticesNumber();
			count += child->getIndicesNumber();
		}
	}

	void DrawableBatch::fillColors(std::vector<Vec4>::iterator colors)
	{
		size_t count = 0;
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			DrawableBatched *child = this->childs[i];
			if (this->dirtyVertices || child->getChanges() & DRAWABLE_BUFFER_COLORS)
			{
				child->fillColors(colors + count);
				child->removeChanges(DRAWABLE_BUFFER_COLORS);
			}
			count += child->getVerticesNumber();
		}
	}

	void DrawableBatch::rebuildVertices()
	{
		this->verticesNumber = 0;
		for (size_t i = 0; i < this->childs.size(); ++i)
			this->verticesNumber += this->childs[i]->getVerticesNumber();
		requireUpdates(DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS);
	}

	void DrawableBatch::rebuildIndices()
	{
		this->indicesNumber = 0;
		for (size_t i = 0; i < this->childs.size(); ++i)
			this->indicesNumber += this->childs[i]->getIndicesNumber();
		requireUpdates(DRAWABLE_BUFFER_INDICES);
	}

	bool DrawableBatch::update()
	{
		for (size_t i = 0; i < this->childs.size(); ++i)
			this->childs[i]->update();
		if (this->dirtyVertices)
			rebuildVertices();
		if (this->dirtyIndices)
			rebuildIndices();
		if (!this->verticesNumber)
			return false;
		return true;
	}

	void DrawableBatch::draw()
	{
		Drawable::draw();
		this->dirtyVertices = false;
		this->dirtyIndices = false;
	}

	void DrawableBatch::addChild(DrawableBatched *child)
	{
		child->setParent(this);
		this->childs.push_back(child);
		if (child->getVerticesNumber())
			setDirtyVertices();
		if (child->getIndicesNumber())
			setDirtyIndices();
	}

	void DrawableBatch::removeChild(DrawableBatched *child)
	{
		for (size_t i = 0; i < this->childs.size(); ++i)
		{
			if (this->childs[i] == child)
			{
				this->childs.erase(this->childs.begin() + i);
				child->setParent(nullptr);
				if (child->getVerticesNumber())
					setDirtyVertices();
				if (child->getIndicesNumber())
					setDirtyIndices();
				requireUpdates(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS);
				return;
			}
		}
	}

	void DrawableBatch::clearChilds()
	{
		for (size_t i = 0; i < this->childs.size(); ++i)
			this->childs[i]->setParent(nullptr);
		this->childs.clear();
		setDirtyVertices();
		setDirtyIndices();
		requireUpdates(DRAWABLE_BUFFER_INDICES | DRAWABLE_BUFFER_TEX_COORDS | DRAWABLE_BUFFER_VERTEXES | DRAWABLE_BUFFER_COLORS);
	}

}
