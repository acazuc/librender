#ifndef LIBRENDER_CONTEXT_H
# define LIBRENDER_CONTEXT_H

# include "../Mat/Mat2.h"
# include "../Mat/Mat3.h"
# include "../Mat/Mat4.h"
# include "../Vec/Vec1.h"
# include "../Vec/Vec2.h"
# include "../Vec/Vec3.h"
# include "../Vec/Vec4.h"
# include <cstdint>
# include <string>

namespace librender
{

	enum ContextRanges
	{
		CONTEXT_MAX_LIGHTS = 0x8,
		CONTEXT_MAX_SAMPLERS = 0x20,
		CONTEXT_MAX_VERTEX_ARRAY_ATTRIBS = 0x10
	};

	union NativeType
	{
		int32_t i;
		uint32_t ui;
		void *p;
	};

	enum BufferType
	{
		BUFFER_TYPE_VERTEX,
		BUFFER_TYPE_INDICE
	};

	enum BufferUsage
	{
		BUFFER_USAGE_STATIC, //D3DPOOL_MANAGED
		BUFFER_USAGE_DYNAMIC, //D3DPOOL_DEFAULT
		BUFFER_USAGE_STREAM, //D3DPOOL_DEFAULT
	};

	struct Buffer
	{
		enum BufferType type;
		enum BufferUsage usage;
		NativeType native;
		bool initialized;
		Buffer() : initialized(false) {};
	};

	enum VertexAttribType
	{
		VERTEX_ATTRIB_BYTE,
		VERTEX_ATTRIB_UNSIGNED_BYTE,
		VERTEX_ATTRIB_SHORT,
		VERTEX_ATTRIB_UNSIGNED_SHORT,
		VERTEX_ATTRIB_INT,
		VERTEX_ATTRIB_UNSIGNED_INT,
		VERTEX_ATTRIB_FLOAT,
		VERTEX_ATTRIB_DOUBLE
	};

	struct VertexAttrib
	{
		enum VertexAttribType type;
		uint8_t size;
		bool changed;
		uint32_t stride;
		uint32_t offset;
		Buffer *buffer;
		VertexAttrib() : buffer(nullptr), changed(false) {};
	};

	enum PrimitiveType
	{
		PRIMITIVE_POINT,
		PRIMITIVE_LINE,
		PRIMITIVE_LINE_STRIP,
		PRIMITIVE_TRIANGLE,
		PRIMITIVE_TRIANGLE_STRIP
	};

	enum ClearBufferBit
	{
		CLEAR_COLOR_BUFFER_BIT = 0x1,
		CLEAR_DEPTH_BUFFER_BIT = 0x2,
		CLEAR_STENCIL_BUFFER_BIT = 0x4
	};

	enum BlendFactor
	{
		BLEND_ZERO,
		BLEND_ONE,
		BLEND_SRC_COLOR,
		BLEND_INV_SRC_COLOR,
		BLEND_DST_COLOR,
		BLEND_INV_DST_COLOR,
		BLEND_SRC_ALPHA,
		BLEND_INV_SRC_ALPHA,
		BLEND_DST_ALPHA,
		BLEND_INV_DST_ALPHA
	};

	enum BlendEquation
	{
		BLEND_ADD,
		BLEND_SUB,
		BLEND_REVERSE_SUB,
		BLEND_MIN,
		BLEND_MAX,
	};

	struct VertexArray
	{
		VertexAttrib attribs[CONTEXT_MAX_VERTEX_ARRAY_ATTRIBS];
		uint32_t attribsUpdateMask;
		NativeType native;
		Buffer *indiceBuffer;
		enum VertexAttribType indiceType;
		bool indiceChanged;
		bool initialized;
		VertexArray() : indiceBuffer(nullptr), indiceType(VERTEX_ATTRIB_UNSIGNED_SHORT), indiceChanged(false), initialized(false) {};
	};

	enum TextureFormat
	{
		TEXTURE_B8G8R8A8,
		TEXTURE_B5G5R5A1,
		TEXTURE_R8G8,
		TEXTURE_R8,
		TEXTURE_BC1,
		TEXTURE_BC2,
		TEXTURE_BC3,
		TEXTURE_BC4,
		TEXTURE_BC5,
	};

	enum TextureType
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_CUBE,
		TEXTURE_1D_ARRAY,
		TEXTURE_2D_ARRAY,
		TEXTURE_CUBE_ARRAY
	};

	struct Texture
	{
		enum TextureType type;
		enum TextureFormat format;
		uint8_t anisotropyLevel;
		uint32_t levels;
		uint32_t width;
		uint32_t height;
		NativeType native;
		bool initialized;
		Texture() : initialized(false) {};
	};

	enum SamplerFilter
	{
		SAMPLER_NEAREST,
		SAMPLER_LINEAR
	};

	enum SamplerMipmapFilter
	{
		SAMPLER_MIPMAP_NONE,
		SAMPLER_MIPMAP_NEAREST,
		SAMPLER_MIPMAP_LINEAR
	};

	enum SamplerWrap
	{
		SAMPLER_REPEAT,
		SAMPLER_MIRRORED_REPEAT,
		SAMPLER_CLAMP_TO_EDGE,
		SAMPLER_CLAMP_TO_BORDER,
		SAMPLER_MIRROR_CLAMP_TO_EDGE
	};

	enum SamplerState
	{
		SAMPLER_MIN_FILTER,
		SAMPLER_MAG_FILTER,
		SAMPLER_MIPMAP,
		SAMPLER_WRAP_S,
		SAMPLER_WRAP_T,
		SAMPLER_WRAP_R,
		SAMPLER_ANISOTROPIC_LEVEL
	};

	enum SamplerChanges
	{
		SAMPLER_CHANGE_MIN_FILTER,
		SAMPLER_CHANGE_MAG_FILTER,
		SAMPLER_CHANGE_MIPMAP,
		SAMPLER_CHANGE_WRAP_S,
		SAMPLER_CHANGE_WRAP_T,
		SAMPLER_CHANGE_WRAP_R,
		SAMPLER_CHANGE_ANISOTROPIC_LEVEL,
		SAMPLER_CHANGE_TEXTURE
	};

	struct Sampler
	{
		enum SamplerMipmapFilter mipmap : 3;
		enum SamplerFilter minFilter : 2;
		enum SamplerFilter magFilter : 2;
		enum SamplerWrap wrapS : 3;
		enum SamplerWrap wrapT : 3;
		enum SamplerWrap wrapR : 3;
		uint32_t anisotropicLevel : 5;
		uint8_t changes;
		Texture *texture;
		NativeType native;
		Sampler() : texture(nullptr), changes(0) {};
	};

	enum FogMode
	{
		FOG_LINEAR,
		FOG_EXP,
		FOG_EXP2
	};

	struct Fog
	{
		enum FogMode mode;
		Vec4 color;
		float density;
		float start;
		float end;
		bool enabled;
	};

	struct Light
	{
		Vec4 ambientColor;
		Vec4 diffuseColor;
		Vec4 specularColor;
		Vec3 pos;
		float attenuations[3];
		bool enabled;
		Light() : enabled(false) {};
	};

	class Window;

	class Context
	{

	friend class Window;

	protected:
		Window *window;
		Fog fog;
		Light lights[CONTEXT_MAX_LIGHTS];
		Sampler samplers[CONTEXT_MAX_SAMPLERS];
		VertexArray defaultVertexArray;
		VertexArray *currentVertexArray;
		Context(Window *window);

	public:
		virtual ~Context();
		virtual void createVertexBuffer(Buffer *buffer) = 0;
		virtual void createIndiceBuffer(Buffer *buffer) = 0;
		virtual void updateBuffer(Buffer *buffer, void *data, uint32_t size) = 0;
		virtual void deleteBuffer(Buffer *buffer) = 0;
		virtual void createVertexArray(VertexArray *vertexArray) = 0;
		virtual void bindVertexArray(VertexArray *vertexArray) = 0;
		virtual void deleteVertexArray(VertexArray *vertexArray) = 0;
		virtual void createTexture(Texture *texture, enum TextureType type, uint32_t width, uint32_t height, enum TextureFormat format, uint32_t levels) = 0;
		virtual void updateTexture(Texture *texture, uint32_t level, void *data, uint32_t len) = 0;
		virtual void getTextureDatas(Texture *texture, uint32_t level, void *data) = 0;
		virtual void deleteTexture(Texture *texture) = 0;
		virtual void setSamplerTexture(uint32_t sampler, Texture *texture) = 0;
		virtual void setSamplerState(uint32_t sampler, enum SamplerState state, uint32_t value) = 0;
		virtual int32_t getAttribLocation(std::string name) = 0;
		virtual void setAttrib(int32_t id, enum VertexAttribType type, uint8_t size, uint32_t stride, uint32_t offset) = 0;
		virtual void setAttribBuffer(int32_t id, Buffer *buffer) = 0;
		virtual void setIndexAttribType(enum VertexAttribType type) = 0;
		virtual void setIndexAttribBuffer(Buffer *buffer) = 0;
		virtual int32_t getUniformLocation(std::string name) = 0;
		virtual void setUniform(int32_t id, TVec1<int32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec2<int32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec3<int32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec4<int32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec1<uint32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec2<uint32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec3<uint32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec4<uint32_t> value) = 0;
		virtual void setUniform(int32_t id, TVec1<float> value) = 0;
		virtual void setUniform(int32_t id, TVec2<float> value) = 0;
		virtual void setUniform(int32_t id, TVec3<float> value) = 0;
		virtual void setUniform(int32_t id, TVec4<float> value) = 0;
		virtual void setUniform(int32_t id, Mat2 value) = 0;
		virtual void setUniform(int32_t id, Mat3 value) = 0;
		virtual void setUniform(int32_t id, Mat4 value) = 0;
		virtual void draw(enum PrimitiveType primitive, uint32_t first, uint32_t count) = 0;
		virtual void drawIndexed(enum PrimitiveType primitive, uint32_t count) = 0;
		virtual void clear(uint32_t color, uint32_t bits) = 0;
		virtual void setDepthRange(double near, double far) = 0;
		virtual void setViewport(int32_t left, int32_t top, int32_t width, int32_t height) = 0;
		virtual void setScissor(int32_t left, int32_t top, int32_t width, int32_t height) = 0;
		virtual void setBlendFunc(enum BlendFactor srcRGB, enum BlendFactor dstRGB, enum BlendFactor srcAlpha, enum BlendFactor dstAlpha) = 0;
		virtual void setBlendFunc(enum BlendFactor src, enum BlendFactor dst) = 0;
		virtual void setBlendEquationSeparate(enum BlendEquation equationRGB, enum BlendEquation equationAlpha) = 0;
		virtual void setBlendEquation(enum BlendEquation equation) = 0;

	};

}

#endif
