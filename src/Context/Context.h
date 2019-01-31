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
		VertexAttrib attribs[0x10];
		uint32_t attribsUpdateMask;
		NativeType native;
		Buffer *indiceBuffer;
		enum VertexAttribType indiceType;
		bool indiceChanged;
		bool initialized;
		VertexArray() : indiceBuffer(nullptr), indiceType(VERTEX_ATTRIB_UNSIGNED_SHORT), indiceChanged(false), initialized(false) {};
	};

	enum TextureFilterType
	{
		TEXTURE_FILTER_NEAREST,
		TEXTURE_FILTER_LINEAR,
		TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST,
		TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR,
	};

	enum TextureWrapType
	{
		TEXTURE_WRAP_REPEAT,
		TEXTURE_WRAP_MIRRORED_REPEAT,
		TEXTURE_WRAP_CLAMP_TO_EDGE,
		TEXTURE_WRAP_CLAMP_TO_BORDER
	};

	enum TextureFormat
	{
		TEXTURE_BGRA8,
		TEXTURE_RGB8,
		TEXTURE_RGB_DXT1,
		TEXTURE_RGBA_DXT1,
		TEXTURE_RGBA_DXT3,
		TEXTURE_RGBA_DXT5,
	};

	struct Texture
	{
		enum TextureFilterType filter;
		enum TextureWrapType wrapS;
		enum TextureWrapType wrapT;
		enum TextureFormat format;
		NativeType native;
		bool initialized;
		Texture() : initialized(false) {};
	};

	class Window;
	class Texture;

	class Context
	{

	friend class Window;

	protected:
		Window *window;
		VertexArray defaultVertexArray;
		VertexArray *currentVertexArray;
		Context(Window *window);

	public:
		virtual ~Context();
		virtual void createVertexBuffer(Buffer *buffer) = 0;
		virtual void createIndiceBuffer(Buffer *buffer) = 0;
		virtual void updateBuffer(Buffer *buffer, void *data, uint32_t size) = 0;
		virtual void bindBuffer(Buffer *buffer) = 0;
		virtual void deleteBuffer(Buffer *buffer) = 0;
		virtual void createVertexArray(VertexArray *vertexArray) = 0;
		virtual void bindVertexArray(VertexArray *vertexArray) = 0;
		virtual void deleteVertexArray(VertexArray *vertexArray) = 0;
		virtual void createTexture(Texture *texture) = 0;
		virtual void updateTexture(Texture *texture) = 0;
		virtual void deleteTexture(Texture *texture) = 0;
		virtual void bindTexture(int32_t id, Texture *texture) = 0;
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
