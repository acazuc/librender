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

	bool OpenGL1Context::textureTypeToGL(enum TextureType textureType, uint32_t *glTarget)
	{
		static_assert(sizeof(*glTarget) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (textureType > TEXTURE_CUBE_ARRAY)
			return false;
		static GLenum values[] = {GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_CUBE_MAP_ARRAY};
		*glTarget = values[textureType];
		return true;
	}

	bool OpenGL1Context::samplerWrapToGL(enum SamplerWrap wrap, uint32_t *glWrap)
	{
		static_assert(sizeof(*glWrap) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (wrap > SAMPLER_MIRROR_CLAMP_TO_EDGE)
			return false;
		static GLenum values[] = {GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRROR_CLAMP_TO_EDGE};
		*glWrap = values[wrap];
		return true;
	}

	bool OpenGL1Context::samplerMinFilterToGL(enum SamplerFilter filter, enum SamplerMipmapFilter mipmapFilter, uint32_t *glFilter)
	{
		static_assert(sizeof(*glFilter) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (filter > SAMPLER_LINEAR || mipmapFilter > SAMPLER_MIPMAP_LINEAR)
			return false;
		static GLenum values[] = {GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR};
		*glFilter = values[filter + mipmapFilter * 2];
		return true;
	}

	bool OpenGL1Context::samplerMagFilterToGL(enum SamplerFilter filter, uint32_t *glFilter)
	{
		static_assert(sizeof(*glFilter) == sizeof(GLenum), "sizeof(GLenum) != sizeof(uint32_t)");
		if (filter > SAMPLER_LINEAR)
			return false;
		static GLenum values[] = {GL_NEAREST, GL_LINEAR};
		*glFilter = values[filter];
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

	void OpenGL1Context::updateAttrib(VertexAttrib *attrib, uint8_t id)
	{
		if (!this->vertexArrayChanged && !attrib->changed)
			return;
		if (!attrib->buffer)
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
		if (!vertexAttribTypeToGL(attrib->type, &type))
			return;
		intptr_t offset = attrib->offset;
		switch (id + 1)
		{
			case 0x1:
				setState(GL1_STATE_CLIENT_VERTEX_ARRAY, true);
				bindBuffer(attrib->buffer);
				glVertexPointer(attrib->size, type, attrib->stride, (void*)offset);
				break;
			case 0x2:
				setState(GL1_STATE_CLIENT_COLOR_ARRAY, true);
				bindBuffer(attrib->buffer);
				glColorPointer(attrib->size, type, attrib->stride, (void*)offset);
				break;
			case 0x3:
				setState(GL1_STATE_CLIENT_SECONDARY_COLOR_ARRAY, true);
				bindBuffer(attrib->buffer);
				glSecondaryColorPointer(attrib->size, type, attrib->stride, (void*)offset);
				break;
			case 0x4:
				setState(GL1_STATE_CLIENT_NORMAL_ARRAY, true);
				bindBuffer(attrib->buffer);
				glNormalPointer(type, attrib->stride, (void*)offset);
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
				bindBuffer(attrib->buffer);
				glTexCoordPointer(attrib->size, type, attrib->stride, (void*)offset);
				break;
		}
		this->currentVertexArray->attribs[id].changed = false;
	}

	void OpenGL1Context::updateAttribs()
	{
		for (uint8_t i = 0; i < CONTEXT_MAX_VERTEX_ARRAY_ATTRIBS; ++i)
			updateAttrib(&this->currentVertexArray->attribs[i], i);
		if ((this->vertexArrayChanged || this->currentVertexArray->indiceChanged) && this->currentVertexArray->indiceBuffer)
			bindBuffer(this->currentVertexArray->indiceBuffer);
		this->vertexArrayChanged = false;
	}

	void OpenGL1Context::updateSampler(Sampler *sampler, uint8_t id)
	{
		if (!sampler->changes)
			return;
		setState(GL1_STATE_ACTIVE_TEXTURE, id);
		if (!sampler->texture)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			goto end;
		}
		GLenum target;
		if (!textureTypeToGL(sampler->texture->type, &target))
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			goto end;
		}
		if (sampler->changes & SAMPLER_CHANGE_TEXTURE)
			sampler->changes = 0xFF;
		glBindTexture(target, sampler->texture->native.ui);
		if (sampler->changes & SAMPLER_CHANGE_MIN_FILTER || sampler->changes & SAMPLER_CHANGE_MIPMAP)
		{
			GLenum filter;
			if (samplerMinFilterToGL(sampler->minFilter, sampler->mipmap, &filter))
				glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
		}
		if (sampler->changes & SAMPLER_CHANGE_MAG_FILTER)
		{
			GLenum filter;
			if (samplerMagFilterToGL(sampler->magFilter, &filter))
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
		}
		if (sampler->changes & SAMPLER_CHANGE_WRAP_S)
		{
			GLenum wrap;
			if (samplerWrapToGL(sampler->wrapS, &wrap))
				glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);
		}
		if (sampler->changes & SAMPLER_CHANGE_WRAP_T)
		{
			GLenum wrap;
			if (samplerWrapToGL(sampler->wrapT, &wrap))
				glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);
		}
		if (sampler->changes & SAMPLER_CHANGE_WRAP_R)
		{
			GLenum wrap;
			if (samplerWrapToGL(sampler->wrapR, &wrap))
				glTexParameteri(target, GL_TEXTURE_WRAP_R, wrap);
		}
		if (sampler->changes & SAMPLER_CHANGE_ANISOTROPIC_LEVEL)
			glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, sampler->anisotropicLevel);
end:
		sampler->changes = 0;
	}

	void OpenGL1Context::updateSamplers()
	{
		for (uint8_t i = 0; i < CONTEXT_MAX_SAMPLERS; ++i)
			updateSampler(&this->samplers[i], i);
	}

	void OpenGL1Context::createVertexBuffer(Buffer *buffer)
	{
		if (!buffer->initialized)
		{
			glGenBuffers(1, &buffer->native.ui);
			buffer->initialized = true;
		}
		buffer->usage = BUFFER_USAGE_STATIC;
		buffer->type = BUFFER_TYPE_VERTEX;
	}

	void OpenGL1Context::createIndiceBuffer(Buffer *buffer)
	{
		if (!buffer->initialized)
		{
			glGenBuffers(1, &buffer->native.ui);
			buffer->initialized = true;
		}
		buffer->usage = BUFFER_USAGE_STATIC;
		buffer->type = BUFFER_TYPE_INDICE;
	}

	void OpenGL1Context::updateBuffer(Buffer *buffer, void *data, uint32_t size)
	{
		if (!buffer->initialized)
			return;
		GLenum usage;
		if (!bufferUsageToGL(buffer->usage, &usage))
			return;
		uint32_t old;
		switch (buffer->type)
		{
			case BUFFER_TYPE_VERTEX:
				old = this->states[GL1_STATE_VERTEX_BUFFER_BOUND];
				setState(GL1_STATE_VERTEX_BUFFER_BOUND, buffer->native.ui);
				break;
			case BUFFER_TYPE_INDICE:
				old = this->states[GL1_STATE_INDICE_BUFFER_BOUND];
				setState(GL1_STATE_INDICE_BUFFER_BOUND, buffer->native.ui);
				break;
			default:
				return;
		}
		bindBuffer(buffer);
		GLenum target;
		if (bufferTypeToGL(buffer->type, &target))
			glBufferData(target, size, data, usage);
		switch (buffer->type)
		{
			case BUFFER_TYPE_VERTEX:
				setState(GL1_STATE_VERTEX_BUFFER_BOUND, old);
				break;
			case BUFFER_TYPE_INDICE:
				setState(GL1_STATE_INDICE_BUFFER_BOUND, old);
				break;
		}
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
		for (uint8_t i = 0; i < CONTEXT_MAX_VERTEX_ARRAY_ATTRIBS; ++i)
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

	void OpenGL1Context::createTexture(Texture *texture, enum TextureType type, uint32_t width, uint32_t height, enum TextureFormat format, uint32_t levels)
	{
		if (!texture->initialized)
		{
			glGenTextures(1, &texture->native.ui);
			texture->initialized = true;
		}
		texture->type = type;
		texture->width = width;
		texture->height = height;
		texture->format = format;
		texture->levels = levels;
	}

	void OpenGL1Context::updateTexture(Texture *texture, uint32_t level, void *data, uint32_t len)
	{
		GLenum glTarget;
		if (!textureTypeToGL(texture->type, &glTarget))
			return;
		glBindTexture(glTarget, texture->native.ui);
		switch (texture->format)
		{
			case TEXTURE_B8G8R8A8:
				glTexImage2D(glTarget, level, GL_RGBA8, texture->width, texture->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
				break;
			case TEXTURE_B5G5R5A1:
				glTexImage2D(glTarget, level, GL_RGB5_A1, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
				break;
			case TEXTURE_R8G8:
				glTexImage2D(glTarget, level, GL_RG8, texture->width, texture->height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
				break;
			case TEXTURE_R8:
				glTexImage2D(glTarget, level, GL_R8, texture->width, texture->height, 0, GL_R, GL_UNSIGNED_BYTE, data);
				break;
			case TEXTURE_BC1:
				//TODO support dynamic conversion if not supported
				glCompressedTexImage2D(glTarget, level, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, texture->width, texture->height, 0, len, data);
				break;
			case TEXTURE_BC2:
				//TODO support dynamic conversion if not supported
				glCompressedTexImage2D(glTarget, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, texture->width, texture->height, 0, len, data);
				break;
			case TEXTURE_BC3:
				//TODO support dynamic conversion if not supported
				glCompressedTexImage2D(glTarget, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, texture->width, texture->height, 0, len, data);
				break;
			case TEXTURE_BC4:
				//TODO support dynamic conversion if not supported
				glCompressedTexImage2D(glTarget, level, GL_COMPRESSED_RED_RGTC1, texture->width, texture->height, 0, len, data);
				break;
			case TEXTURE_BC5:
				//TODO support dynamic conversion if not supported
				glCompressedTexImage2D(glTarget, level, GL_COMPRESSED_RG_RGTC2, texture->width, texture->height, 0, len, data);
				break;
		}
	}

	void OpenGL1Context::getTextureDatas(Texture *texture, uint32_t level, void *data)
	{
		if (!texture->initialized)
			return;
		GLenum glTarget;
		if (!textureTypeToGL(texture->type, &glTarget))
			return;
		glBindTexture(glTarget, texture->native.ui);
		switch (texture->format)
		{
			case TEXTURE_B8G8R8A8:
				glGetTexImage(glTarget, level, GL_BGRA, GL_UNSIGNED_BYTE, data);
				break;
			case TEXTURE_B5G5R5A1:
				glGetTexImage(glTarget, level, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
				break;
			case TEXTURE_R8G8:
				glGetTexImage(glTarget, level, GL_RG, GL_UNSIGNED_BYTE, data);
				break;
			case TEXTURE_R8:
				glGetTexImage(glTarget, level, GL_RED, GL_UNSIGNED_BYTE, data);
				break;
			case TEXTURE_BC1:
			case TEXTURE_BC2:
			case TEXTURE_BC3:
			case TEXTURE_BC4:
			case TEXTURE_BC5:
				glGetCompressedTexImage(glTarget, level, data);
				break;
		}
	}

	void OpenGL1Context::deleteTexture(Texture *texture)
	{
		if (!texture->initialized)
			return;
		for (uint32_t i = 0; i < CONTEXT_MAX_SAMPLERS; ++i)
		{
			if (this->samplers[i].texture == texture)
				setSamplerTexture(i, texture);
		}
		glDeleteTextures(1, &texture->native.ui);
		texture->initialized = false;
	}

	void OpenGL1Context::setSamplerTexture(uint32_t sampler, Texture *texture)
	{
		if (sampler >= CONTEXT_MAX_SAMPLERS)
			return;
		this->samplers[sampler].texture = texture;
		this->samplers[sampler].changes |= SAMPLER_CHANGE_TEXTURE;
	}

	void OpenGL1Context::setSamplerState(uint32_t sampler, enum SamplerState state, uint32_t value)
	{
		if (sampler >= CONTEXT_MAX_SAMPLERS)
			return;
		switch (state)
		{
			case SAMPLER_MIN_FILTER:
				if (this->samplers[sampler].minFilter == value)
					break;
				this->samplers[sampler].minFilter = static_cast<enum SamplerFilter>(value);
				this->samplers[sampler].changes |= SAMPLER_CHANGE_MIN_FILTER;
				break;
			case SAMPLER_MAG_FILTER:
				if (this->samplers[sampler].magFilter == value)
					break;
				this->samplers[sampler].magFilter = static_cast<enum SamplerFilter>(value);
				this->samplers[sampler].changes |= SAMPLER_CHANGE_MAG_FILTER;
				break;
			case SAMPLER_MIPMAP:
				if (this->samplers[sampler].mipmap == value)
					break;
				this->samplers[sampler].mipmap = static_cast<enum SamplerMipmapFilter>(value);
				this->samplers[sampler].changes |= SAMPLER_CHANGE_MIPMAP;
				break;
			case SAMPLER_WRAP_S:
				if (this->samplers[sampler].wrapS == value)
					break;
				this->samplers[sampler].wrapS = static_cast<enum SamplerWrap>(value);
				this->samplers[sampler].changes |= SAMPLER_CHANGE_WRAP_S;
				break;
			case SAMPLER_WRAP_T:
				if (this->samplers[sampler].wrapT == value)
					break;
				this->samplers[sampler].wrapT = static_cast<enum SamplerWrap>(value);
				this->samplers[sampler].changes |= SAMPLER_CHANGE_WRAP_T;
				break;
			case SAMPLER_WRAP_R:
				if (this->samplers[sampler].wrapR == value)
					break;
				this->samplers[sampler].wrapR = static_cast<enum SamplerWrap>(value);
				this->samplers[sampler].changes |= SAMPLER_CHANGE_WRAP_R;
				break;
			case SAMPLER_ANISOTROPIC_LEVEL:
				if (this->samplers[sampler].anisotropicLevel == value)
					break;
				this->samplers[sampler].anisotropicLevel = value;
				this->samplers[sampler].changes |= SAMPLER_CHANGE_ANISOTROPIC_LEVEL;
				break;
		}
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
		if (id <= 0 || id > CONTEXT_MAX_VERTEX_ARRAY_ATTRIBS)
			return;
		this->currentVertexArray->attribs[id - 1].type = type;
		this->currentVertexArray->attribs[id - 1].size = size;
		this->currentVertexArray->attribs[id - 1].stride = stride;
		this->currentVertexArray->attribs[id - 1].offset = offset;
		this->currentVertexArray->attribs[id - 1].changed = true;
	}

	void OpenGL1Context::setAttribBuffer(int32_t id, Buffer *buffer)
	{
		if (id <= 0 || id > CONTEXT_MAX_VERTEX_ARRAY_ATTRIBS)
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
		if (!name.compare("fog_color"))
			return 0x5;
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
		switch (id)
		{
			case 0x5:
				glFogiv(GL_FOG_COLOR, &value[0]);
				break;
		}
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
		switch (id)
		{
			case 0x5:
				glFogiv(GL_FOG_COLOR, reinterpret_cast<const int32_t*>(&value[0]));
				break;
		}
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
		switch (id)
		{
			case 0x5:
				glFogfv(GL_FOG_COLOR, &value[0]);
				break;
		}
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
		updateSamplers();
		GLenum glPrimitive;
		if (!primitiveTypeToGL(primitive, &glPrimitive))
			return;
		glDrawArrays(glPrimitive, first, count);
	}

	void OpenGL1Context::drawIndexed(enum PrimitiveType primitive, uint32_t count)
	{
		updateAttribs();
		updateSamplers();
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
