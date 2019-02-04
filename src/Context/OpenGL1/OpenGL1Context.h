#ifndef LIBRENDER_OPENGL1_CONTEXT_H
# define LIBRENDER_OPENGL1_CONTEXT_H

# include "../Context.h"

namespace librender
{

	enum OpenGL1State
	{
		GL1_STATE_CLIENT_VERTEX_ARRAY,
		GL1_STATE_CLIENT_COLOR_ARRAY,
		GL1_STATE_CLIENT_SECONDARY_COLOR_ARRAY,
		GL1_STATE_CLIENT_NORMAL_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD0_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD1_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD2_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD3_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD4_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD5_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD6_ARRAY,
		GL1_STATE_CLIENT_TEX_COORD7_ARRAY,
		GL1_STATE_CLIENT_ACTIVE_TEXTURE,
		GL1_STATE_MATRIX_MODE,
		GL1_STATE_BLEND_FUNC,
		GL1_STATE_BLEND_EQUATION,
		GL1_STATE_VERTEX_BUFFER_BOUND,
		GL1_STATE_INDICE_BUFFER_BOUND,
		GL1_STATE_ACTIVE_TEXTURE,
		GL1_STATE_TEXTURE0_TYPE,
		GL1_STATE_TEXTURE1_TYPE,
		GL1_STATE_TEXTURE2_TYPE,
		GL1_STATE_TEXTURE3_TYPE,
		GL1_STATE_TEXTURE4_TYPE,
		GL1_STATE_TEXTURE5_TYPE,
		GL1_STATE_TEXTURE6_TYPE,
		GL1_STATE_TEXTURE7_TYPE,
		GL1_STATE_TEXTURE0,
		GL1_STATE_TEXTURE1,
		GL1_STATE_TEXTURE2,
		GL1_STATE_TEXTURE3,
		GL1_STATE_TEXTURE4,
		GL1_STATE_TEXTURE5,
		GL1_STATE_TEXTURE6,
		GL1_STATE_TEXTURE7,
		GL1_STATE_LAST
	};

	class OpenGL1Context : public Context
	{

	friend class Window;

	protected:
		bool vertexAttribTypeToGL(enum VertexAttribType type, uint32_t *glType);
		bool bufferTypeToGL(enum BufferType type, uint32_t *glType);
		bool bufferUsageToGL(enum BufferUsage usage, uint32_t *glUsage);
		bool primitiveTypeToGL(enum PrimitiveType primitive, uint32_t *glPrimitive);
		bool blendFactorToGL(enum BlendFactor factor, uint32_t *glFactor);
		bool blendEquationToGL(enum BlendEquation equation, uint32_t *glEquation);
		bool textureTypeToGL(enum TextureType type, uint32_t *glTarget);
		bool samplerWrapToGL(enum SamplerWrap wrap, uint32_t *glWrap);
		bool samplerMinFilterToGL(enum SamplerFilter filter, enum SamplerMipmapFilter mipmapFilter, uint32_t *glFilter);
		bool samplerMagFilterToGL(enum SamplerFilter filter, uint32_t *glFilter);
		bool hasAnisotropicFiltering;
		bool vertexArrayChanged;
		uint32_t states[GL1_STATE_LAST];
		void setState(enum OpenGL1State state, uint32_t value);
		void updateAttrib(VertexAttrib *attrib, uint8_t id);
		void updateAttribs();
		void updateSampler(Sampler *sampler, uint8_t id);
		void updateSamplers();
		void bindBuffer(Buffer *buffer);
		void bindTexture(Texture *texture);
		OpenGL1Context(Window *window);

	public:
		~OpenGL1Context();
		void createVertexBuffer(Buffer *buffer);
		void createIndiceBuffer(Buffer *buffer);
		void updateBuffer(Buffer *buffer, void *data, uint32_t size);
		void deleteBuffer(Buffer *buffer);
		void createVertexArray(VertexArray *vertexArray);
		void bindVertexArray(VertexArray *vertexArray);
		void deleteVertexArray(VertexArray *vertexArray);
		void createTexture(Texture *texture, enum TextureType type, uint32_t width, uint32_t height, enum TextureFormat format, uint32_t levels);
		void updateTexture(Texture *texture, uint32_t level, void *data, uint32_t len);
		void getTextureDatas(Texture *texture, uint32_t level, void *data);
		void deleteTexture(Texture *texture);
		void setSamplerTexture(uint32_t sampler, Texture *texture);
		void setSamplerState(uint32_t sampler, enum SamplerState state, uint32_t value);
		int32_t getAttribLocation(std::string name);
		void setAttrib(int32_t id, enum VertexAttribType type, uint8_t size, uint32_t stride, uint32_t offset);
		void setAttribBuffer(int32_t id, Buffer *buffer);
		void setIndexAttribType(enum VertexAttribType type);
		void setIndexAttribBuffer(Buffer *buffer);
		int32_t getUniformLocation(std::string name);
		void setUniform(int32_t id, TVec1<int32_t> value);
		void setUniform(int32_t id, TVec2<int32_t> value);
		void setUniform(int32_t id, TVec3<int32_t> value);
		void setUniform(int32_t id, TVec4<int32_t> value);
		void setUniform(int32_t id, TVec1<uint32_t> value);
		void setUniform(int32_t id, TVec2<uint32_t> value);
		void setUniform(int32_t id, TVec3<uint32_t> value);
		void setUniform(int32_t id, TVec4<uint32_t> value);
		void setUniform(int32_t id, TVec1<float> value);
		void setUniform(int32_t id, TVec2<float> value);
		void setUniform(int32_t id, TVec3<float> value);
		void setUniform(int32_t id, TVec4<float> value);
		void setUniform(int32_t id, Mat2 value);
		void setUniform(int32_t id, Mat3 value);
		void setUniform(int32_t id, Mat4 value);
		void draw(enum PrimitiveType primitive, uint32_t first, uint32_t count);
		void drawIndexed(enum PrimitiveType primitive, uint32_t count);
		void clear(uint32_t color, uint32_t bits);
		void setDepthRange(double near, double far);
		void setViewport(int32_t left, int32_t top, int32_t width, int32_t height);
		void setScissor(int32_t left, int32_t top, int32_t width, int32_t height);
		void setBlendFunc(enum BlendFactor srcRGB, enum BlendFactor dstRGB, enum BlendFactor srcAlpha, enum BlendFactor dstAlpha);
		void setBlendFunc(enum BlendFactor src, enum BlendFactor dst);
		void setBlendEquationSeparate(enum BlendEquation equationRGB, enum BlendEquation equationAlpha);
		void setBlendEquation(enum BlendEquation equation);

	};

}

#endif
