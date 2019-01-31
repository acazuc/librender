#include "OpenGL1Context.h"
#include "../../Window/Window.h"
#include "../../GL.h"

namespace librender
{

	OpenGL1Context::OpenGL1Context(Window *window)
	: Context(window)
	, vertexArrayChanged(false)
	{
		states[GL1_STATE_CLIENT_VERTEX_ARRAY] = false;
		states[GL1_STATE_CLIENT_COLOR_ARRAY] = false;
		states[GL1_STATE_CLIENT_SECONDARY_COLOR_ARRAY] = false;
		states[GL1_STATE_CLIENT_NORMAL_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD0_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD1_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD2_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD3_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD4_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD5_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD6_ARRAY] = false;
		states[GL1_STATE_CLIENT_TEX_COORD7_ARRAY] = false;
		states[GL1_STATE_CLIENT_ACTIVE_TEXTURE] = 0;
		states[GL1_STATE_MATRIX_MODE] = GL_MODELVIEW;
		states[GL1_STATE_BLEND_FUNC] = (BLEND_ONE << 24) | (BLEND_ZERO << 16) | (BLEND_ONE << 8) | BLEND_ZERO;
		states[GL1_STATE_BLEND_EQUATION] = (BLEND_ADD << 8) | BLEND_ADD;
		states[GL1_STATE_VERTEX_BUFFER_BOUND] = 0;
		states[GL1_STATE_INDICE_BUFFER_BOUND] = 0;
		states[GL1_STATE_ACTIVE_TEXTURE] = 0;
		states[GL1_STATE_TEXTURE_BOUND] = 0;
	}

	OpenGL1Context::~OpenGL1Context()
	{
	}

	bool OpenGL1Context::vertexAttribTypeToGL(enum VertexAttribType type, uint32_t *glType)
	{
		static_assert(sizeof(*glType) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (type > VERTEX_ATTRIB_DOUBLE)
			return false;
		static GLenum values[] = {GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE};
		*glType = values[type];
		return true;
	}

	bool OpenGL1Context::bufferTypeToGL(enum BufferType type, uint32_t *glType)
	{
		static_assert(sizeof(*glType) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (type > BUFFER_TYPE_INDICE)
			return false;
		static GLenum values[] = {GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER};
		*glType = values[type];
		return true;
	}

	bool OpenGL1Context::bufferUsageToGL(enum BufferUsage usage, uint32_t *glUsage)
	{
		static_assert(sizeof(*glUsage) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (usage > BUFFER_USAGE_STREAM)
			return false;
		static GLenum values[] = {GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW};
		*glUsage = values[usage];
		return true;
	}

	bool OpenGL1Context::primitiveTypeToGL(enum PrimitiveType primitive, uint32_t *glPrimitive)
	{
		static_assert(sizeof(*glPrimitive) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (primitive > PRIMITIVE_TRIANGLE_STRIP)
			return false;
		static GLenum values[] = {GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP};
		*glPrimitive = values[primitive];
		return true;
	}

	bool OpenGL1Context::blendFactorToGL(enum BlendFactor factor, uint32_t *glFactor)
	{
		static_assert(sizeof(*glFactor) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (factor > BLEND_INV_DST_ALPHA)
			return false;
		static GLenum values[] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};
		*glFactor = values[factor];
		return true;
	}

	bool OpenGL1Context::blendEquationToGL(enum BlendEquation equation, uint32_t *glEquation)
	{
		static_assert(sizeof(*glEquation) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (equation > BLEND_MAX)
			return false;
		static GLenum values[] = {GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX};
		*glEquation = values[equation];
		return true;
	}

	void OpenGL1Context::setState(enum OpenGL1State state, uint32_t value)
	{
		if (state >= GL1_STATE_LAST)
			return;
		if (this->states[state] == value)
			return;
		switch (state)
		{
			case GL1_STATE_CLIENT_VERTEX_ARRAY:
				if (value)
					glEnableClientState(GL_VERTEX_ARRAY);
				else
					glDisableClientState(GL_VERTEX_ARRAY);
				break;
			case GL1_STATE_CLIENT_COLOR_ARRAY:
				if (value)
					glEnableClientState(GL_COLOR_ARRAY);
				else
					glDisableClientState(GL_COLOR_ARRAY);
				break;
			case GL1_STATE_CLIENT_SECONDARY_COLOR_ARRAY:
				if (value)
					glEnableClientState(GL_SECONDARY_COLOR_ARRAY);
				else
					glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
				break;
			case GL1_STATE_CLIENT_NORMAL_ARRAY:
				if (value)
					glEnableClientState(GL_NORMAL_ARRAY);
				else
					glDisableClientState(GL_NORMAL_ARRAY);
				break;
			case GL1_STATE_CLIENT_TEX_COORD0_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD1_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD2_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD3_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD4_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD5_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD6_ARRAY:
			case GL1_STATE_CLIENT_TEX_COORD7_ARRAY:
				setState(GL1_STATE_CLIENT_ACTIVE_TEXTURE, state - GL1_STATE_CLIENT_TEX_COORD0_ARRAY);
				if (value)
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				else
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				break;
			case GL1_STATE_CLIENT_ACTIVE_TEXTURE:
				glClientActiveTexture(GL_TEXTURE0 + value);
				break;
			case GL1_STATE_MATRIX_MODE:
				glMatrixMode(value);
				break;
			case GL1_STATE_BLEND_FUNC:
				GLenum glSrcRGB;
				GLenum glDstRGB;
				GLenum glSrcAlpha;
				GLenum glDstAlpha;
				if (!blendFactorToGL(static_cast<enum BlendFactor>((value >> 24) & 0xFF), &glSrcRGB))
					break;
				if (!blendFactorToGL(static_cast<enum BlendFactor>((value >> 16) & 0xFF), &glDstRGB))
					break;
				if (!blendFactorToGL(static_cast<enum BlendFactor>((value >> 8) & 0xFF), &glSrcAlpha))
					break;
				if (!blendFactorToGL(static_cast<enum BlendFactor>(value & 0xFF), &glDstAlpha))
					break;
				glBlendFuncSeparate(glSrcRGB, glDstRGB, glSrcAlpha, glDstAlpha);
				break;
			case GL1_STATE_BLEND_EQUATION:
				GLenum glEquationRGB;
				GLenum glEquationAlpha;
				if (!blendEquationToGL(static_cast<enum BlendEquation>((value >> 8) & 0xFF), &glEquationRGB))
					break;
				if (!blendEquationToGL(static_cast<enum BlendEquation>(value & 0xFF), &glEquationAlpha))
					break;
				glBlendEquationSeparate(glEquationRGB, glEquationAlpha);
				break;
			case GL1_STATE_VERTEX_BUFFER_BOUND:
				glBindBuffer(GL_ARRAY_BUFFER, value);
				break;
			case GL1_STATE_INDICE_BUFFER_BOUND:
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, value);
				break;
			case GL1_STATE_ACTIVE_TEXTURE:
				glActiveTexture(GL_TEXTURE0 + value);
				break;
			case GL1_STATE_TEXTURE_BOUND:
				glBindTexture(GL_TEXTURE_2D, value);
				break;
		}
		this->states[state] = value;
	}

	void OpenGL1Context::updateAttrib(uint8_t id)
	{
		if (!this->vertexArrayChanged && !this->currentVertexArray->attribs[id].changed)
			return;
		if (!this->currentVertexArray->attribs[id].buffer)
		{
			switch (id + 1)
			{
				case 0x1:
					setState(GL1_STATE_CLIENT_VERTEX_ARRAY, false);
					break;
				case 0x2:
					setState(GL1_STATE_CLIENT_COLOR_ARRAY, false);
					break;
				case 0x3:
					setState(GL1_STATE_CLIENT_SECONDARY_COLOR_ARRAY, false);
					break;
				case 0x4:
					setState(GL1_STATE_CLIENT_NORMAL_ARRAY, false);
					break;
				case 0x5:
				case 0x6:
				case 0x7:
				case 0x8:
				case 0x9:
				case 0xA:
				case 0xB:
				case 0xC:
					setState(static_cast<enum OpenGL1State>(GL1_STATE_CLIENT_TEX_COORD0_ARRAY + (id + 1) - 0x5), false);
					break;
			}
			return;
		}
		GLenum type;
		if (!vertexAttribTypeToGL(this->currentVertexArray->attribs[id].type, &type))
			return;
		intptr_t offset = this->currentVertexArray->attribs[id].offset;
		switch (id + 1)
		{
			case 0x1:
				setState(GL1_STATE_CLIENT_VERTEX_ARRAY, true);
				bindBuffer(this->currentVertexArray->attribs[id].buffer);
				glVertexPointer(this->currentVertexArray->attribs[id].size, type, this->currentVertexArray->attribs[id].stride, (void*)offset);
				break;
			case 0x2:
				setState(GL1_STATE_CLIENT_COLOR_ARRAY, true);
				bindBuffer(this->currentVertexArray->attribs[id].buffer);
				glColorPointer(this->currentVertexArray->attribs[id].size, type, this->currentVertexArray->attribs[id].stride, (void*)offset);
				break;
			case 0x3:
				setState(GL1_STATE_CLIENT_SECONDARY_COLOR_ARRAY, true);
				bindBuffer(this->currentVertexArray->attribs[id].buffer);
				glSecondaryColorPointer(this->currentVertexArray->attribs[id].size, type, this->currentVertexArray->attribs[id].stride, (void*)offset);
				break;
			case 0x4:
				setState(GL1_STATE_CLIENT_NORMAL_ARRAY, true);
				bindBuffer(this->currentVertexArray->attribs[id].buffer);
				glNormalPointer(type, this->currentVertexArray->attribs[id].stride, (void*)offset);
				break;
			case 0x5:
			case 0x6:
			case 0x7:
			case 0x8:
			case 0x9:
			case 0xA:
			case 0xB:
			case 0xC:
				setState(static_cast<enum OpenGL1State>(GL1_STATE_CLIENT_TEX_COORD0_ARRAY + (id + 1) - 0x5), true);
				bindBuffer(this->currentVertexArray->attribs[id].buffer);
				glTexCoordPointer(this->currentVertexArray->attribs[id].size, type, this->currentVertexArray->attribs[id].stride, (void*)offset);
				break;
		}
		this->currentVertexArray->attribs[id].changed = false;
	}

	void OpenGL1Context::updateAttribs()
	{
		for (uint8_t i = 0; i < 0x10; ++i)
			updateAttrib(i);
		if ((this->vertexArrayChanged || this->currentVertexArray->indiceChanged) && this->currentVertexArray->indiceBuffer)
			bindBuffer(this->currentVertexArray->indiceBuffer);
		this->vertexArrayChanged = false;
	}

	void OpenGL1Context::createVertexBuffer(Buffer *buffer)
	{
		if (!buffer->initialized)
			glGenBuffers(1, &buffer->native.ui);
		buffer->usage = BUFFER_USAGE_STATIC;
		buffer->type = BUFFER_TYPE_VERTEX;
		buffer->initialized = true;
	}

	void OpenGL1Context::createIndiceBuffer(Buffer *buffer)
	{
		if (!buffer->initialized)
			glGenBuffers(1, &buffer->native.ui);
		buffer->usage = BUFFER_USAGE_STATIC;
		buffer->type = BUFFER_TYPE_INDICE;
		buffer->initialized = true;
	}

	void OpenGL1Context::updateBuffer(Buffer *buffer, void *data, uint32_t size)
	{
		if (!buffer->initialized)
			return;
		GLenum usage;
		if (!bufferUsageToGL(buffer->usage, &usage))
			return;
		bindBuffer(buffer);
		GLenum target;
		if (!bufferTypeToGL(buffer->type, &target))
			return;
		glBufferData(target, size, data, usage);
	}

	void OpenGL1Context::bindBuffer(Buffer *buffer)
	{
		if (!buffer->initialized)
			return;
		switch (buffer->type)
		{
			case BUFFER_TYPE_VERTEX:
				setState(GL1_STATE_VERTEX_BUFFER_BOUND, buffer->native.ui);
				break;
			case BUFFER_TYPE_INDICE:
				setState(GL1_STATE_INDICE_BUFFER_BOUND, buffer->native.ui);
				break;
		}
	}

	void OpenGL1Context::deleteBuffer(Buffer *buffer)
	{
		for (uint8_t i = 0; i <= 0x10; ++i)
		{
			if (this->currentVertexArray->attribs[i].buffer == buffer)
				setAttribBuffer(i, nullptr);
		}
		if (!buffer->initialized)
			return;
		glDeleteBuffers(1, &buffer->native.ui);
	}

	void OpenGL1Context::createVertexArray(VertexArray *vertexArray)
	{
		vertexArray->initialized = true;
	}

	void OpenGL1Context::bindVertexArray(VertexArray *vertexArray)
	{
		if (!vertexArray)
			vertexArray = &this->defaultVertexArray;
		if (!vertexArray->initialized)
			return;
		if (vertexArray == this->currentVertexArray)
			return;
		this->currentVertexArray = vertexArray;
		this->vertexArrayChanged = true;
	}

	void OpenGL1Context::deleteVertexArray(VertexArray *vertexArray)
	{
		if (vertexArray == this->currentVertexArray)
			this->currentVertexArray = &this->defaultVertexArray;
		if (vertexArray != &this->defaultVertexArray)
			vertexArray->initialized = false;
	}

	void OpenGL1Context::createTexture(Texture *texture)
	{
		//texture->initialized = true;
	}

	void OpenGL1Context::updateTexture(Texture *texture)
	{
	}

	void OpenGL1Context::deleteTexture(Texture *texture)
	{
		//texture->initalized = false;
	}

	void OpenGL1Context::bindTexture(int32_t id, Texture *texture)
	{
		if (id > 7)
			return;
		setState(GL1_STATE_ACTIVE_TEXTURE, id);
		//setState(GL1_STATE_TEXTURE_BOUND, texture ? texture->getId() : 0);
	}

	int32_t OpenGL1Context::getAttribLocation(std::string name)
	{
		if (!name.compare("vertex"))
			return 0x1;
		if (!name.compare("color"))
			return 0x2;
		if (!name.compare("color2"))
			return 0x3;
		if (!name.compare("normal"))
			return 0x4;
		if (!name.compare("texture0"))
			return 0x5;
		if (!name.compare("texture1"))
			return 0x6;
		if (!name.compare("texture2"))
			return 0x7;
		if (!name.compare("texture3"))
			return 0x8;
		if (!name.compare("texture4"))
			return 0x9;
		if (!name.compare("texture5"))
			return 0xA;
		if (!name.compare("texture6"))
			return 0xB;
		if (!name.compare("texture7"))
			return 0xC;
		return -1;
	}

	void OpenGL1Context::setAttrib(int32_t id, enum VertexAttribType type, uint8_t size, uint32_t stride, uint32_t offset)
	{
		if (id <= 0 || id > 0xC)
			return;
		this->currentVertexArray->attribs[id - 1].type = type;
		this->currentVertexArray->attribs[id - 1].size = size;
		this->currentVertexArray->attribs[id - 1].stride = stride;
		this->currentVertexArray->attribs[id - 1].offset = offset;
		this->currentVertexArray->attribs[id - 1].changed = true;
	}

	void OpenGL1Context::setAttribBuffer(int32_t id, Buffer *buffer)
	{
		if (id <= 0 || id > 0xC)
			return;
		this->currentVertexArray->attribs[id - 1].buffer = buffer;
		this->currentVertexArray->attribs[id - 1].changed = true;
	}

	void OpenGL1Context::setIndexAttribType(enum VertexAttribType type)
	{
		this->currentVertexArray->indiceType = type;
	}

	void OpenGL1Context::setIndexAttribBuffer(Buffer *buffer)
	{
		this->currentVertexArray->indiceBuffer = buffer;
		this->currentVertexArray->indiceChanged = true;
	}

	int OpenGL1Context::getUniformLocation(std::string name)
	{
		if (!name.compare("matrix_projection"))
			return 0x1;
		if (!name.compare("matrix_modelview"))
			return 0x2;
		if (!name.compare("matrix_color"))
			return 0x3;
		if (!name.compare("matrix_texture"))
			return 0x4;
		return -1;
	}

	void OpenGL1Context::setUniform(int32_t id, TVec1<int32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec2<int32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec3<int32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec4<int32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec1<uint32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec2<uint32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec3<uint32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec4<uint32_t> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec1<float> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec2<float> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec3<float> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, TVec4<float> value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, Mat2 value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, Mat3 value)
	{
	}

	void OpenGL1Context::setUniform(int32_t id, Mat4 value)
	{
		switch (id)
		{
			case 0x1:
				setState(GL1_STATE_MATRIX_MODE, GL_PROJECTION);
				glLoadMatrixf(&value[0][0]);
				break;
			case 0x2:
				setState(GL1_STATE_MATRIX_MODE, GL_MODELVIEW);
				glLoadMatrixf(&value[0][0]);
				break;
			case 0x3:
				setState(GL1_STATE_MATRIX_MODE, GL_COLOR);
				glLoadMatrixf(&value[0][0]);
				break;
			case 0x4:
				setState(GL1_STATE_MATRIX_MODE, GL_TEXTURE);
				glLoadMatrixf(&value[0][0]);
				break;
		}
	}

	void OpenGL1Context::draw(enum PrimitiveType primitive, uint32_t first, uint32_t count)
	{
		updateAttribs();
		GLenum glPrimitive;
		if (!primitiveTypeToGL(primitive, &glPrimitive))
			return;
		glDrawArrays(glPrimitive, first, count);
	}

	void OpenGL1Context::drawIndexed(enum PrimitiveType primitive, uint32_t count)
	{
		updateAttribs();
		GLenum glPrimitive;
		if (!primitiveTypeToGL(primitive, &glPrimitive))
			return;
		GLenum glIndiceType;
		if (!vertexAttribTypeToGL(this->currentVertexArray->indiceType, &glIndiceType))
			return;
		glDrawElements(glPrimitive, count, glIndiceType, nullptr);
	}

	void OpenGL1Context::clear(uint32_t color, uint32_t bits)
	{
		GLbitfield buffers = 0;
		if (bits & CLEAR_COLOR_BUFFER_BIT)
			buffers |= GL_COLOR_BUFFER_BIT;
		if (bits & CLEAR_DEPTH_BUFFER_BIT)
			buffers |= GL_DEPTH_BUFFER_BIT;
		if (bits & CLEAR_STENCIL_BUFFER_BIT)
			buffers |= GL_STENCIL_BUFFER_BIT;
		glClearColor(((color >> 24) & 0xff) / 255., ((color >> 16) & 0xff) / 255., ((color >> 8) & 0xff) / 255., (color & 0xff) / 255.);
		glClear(buffers);
	}

	void OpenGL1Context::setDepthRange(double near, double far)
	{
		glDepthRange(near, far);
	}

	void OpenGL1Context::setViewport(int32_t left, int32_t top, int32_t width, int32_t height)
	{
		glViewport(left, top, width, height);
	}

	void OpenGL1Context::setScissor(int32_t left, int32_t top, int32_t width, int32_t height)
	{
		glScissor(left, this->window->getHeight() - top + height, width, height);
	}

	void OpenGL1Context::setBlendFunc(enum BlendFactor srcRGB, enum BlendFactor dstRGB, enum BlendFactor srcAlpha, enum BlendFactor dstAlpha)
	{
		setState(GL1_STATE_BLEND_FUNC, ((srcRGB & 0xFF) << 24) | ((dstRGB & 0xFF) << 16) | ((srcAlpha & 0xFF) << 8) | (dstAlpha & 0xFF));
	}

	void OpenGL1Context::setBlendFunc(enum BlendFactor src, enum BlendFactor dst)
	{
		setBlendFunc(src, dst, src, dst);
	}

	void OpenGL1Context::setBlendEquationSeparate(enum BlendEquation equationRGB, enum BlendEquation equationAlpha)
	{
		setState(GL1_STATE_BLEND_EQUATION, ((equationRGB & 0xFF) << 8) | (equationAlpha & 0xFF));
	}

	void OpenGL1Context::setBlendEquation(enum BlendEquation equation)
	{
		setBlendEquationSeparate(equation, equation);
	}

}
