NAME = librender.a

CXX = g++

override CXXLFAGS += -std=c++14 -Wall -Wextra -O3 -pipe

AR = ar

ARFLAGS = rc

RANLIB = ranlib

RANLIBFLAGS =

INCLUDES_PATH = -I src
INCLUDES_PATH+= -I lib
INCLUDES_PATH+= -I lib/glfw/include
INCLUDES_PATH+= -I lib/freetype/include
INCLUDES_PATH+= -I lib/glad/include
INCLUDES_PATH+= -I lib/libunicode/include

SRCS_PATH = src/

SRCS_NAME = Color.cpp \
	    Draw.cpp \
	    Drawable.cpp \
	    DrawableBase.cpp \
	    DrawableBatch.cpp \
	    DrawableBatched.cpp \
	    DrawableTessellator.cpp \
	    Text/Text.cpp \
	    Text/TextBase.cpp \
	    Text/TextBatch.cpp \
	    Text/TextBatched.cpp \
	    Text/TextTessellator.cpp \
	    Font/FontModel.cpp \
	    Font/Font.cpp \
	    Font/Glyph.cpp \
	    Window/EventsManager.cpp \
	    Window/Window.cpp \
	    Window/Monitor.cpp \
	    Window/VideoMode.cpp \
	    Sprite/Sprite.cpp \
	    Sprite/SpriteBase.cpp \
	    Sprite/SpriteBatch.cpp \
	    Sprite/SpriteBatched.cpp \
	    Sprite/SpriteTessellator.cpp \
	    Texture/Texture.cpp \
	    Shape/Shape.cpp \
	    Shape/Rectangle.cpp \
	    Shape/RectangleBorder.cpp \
	    Shape/Line.cpp \
	    Shape/Disk.cpp \
	    Shape/Circle.cpp \
	    Shape/Triangle.cpp \
	    Shape/TriangleBorder.cpp \
	    Shader/FragmentShader.cpp \
	    Shader/GeometryShader.cpp \
	    Shader/VertexShader.cpp \
	    Shader/Program.cpp \
	    Shader/VertexBuffer.cpp \
	    Shader/VertexArray.cpp \
	    Shader/RenderBuffer.cpp \
	    Shader/ProgramLocation.cpp \
	    Shader/FrameBuffer.cpp \
	    Shader/Shader.cpp \
	    Shader/Sprite/ShaderSprite.cpp \
	    Shader/Sprite/ShaderSpriteBatch.cpp \
	    Shader/Sprite/ShaderSpriteBatchEntry.cpp \
	    Shader/Sprite/ShaderSpriteEntry.cpp \
	    Shader/Text/ShaderText.cpp \
	    Shader/Text/ShaderTextBatch.cpp \
	    Shader/Text/ShaderTextBatchEntry.cpp \
	    Shader/Text/ShaderTextEntry.cpp \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.opp)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(NAME)

$(NAME): $(OBJS)
	@echo "AR $(NAME)"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "RANLIB $(NAME)"
	@$(RANLIB) $(RANLIBFLAGS) $(NAME)

$(OBJS_PATH)%.opp: $(SRCS_PATH)%.cpp
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDES_PATH)

odir:
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)Window
	@mkdir -p $(OBJS_PATH)Text
	@mkdir -p $(OBJS_PATH)Font
	@mkdir -p $(OBJS_PATH)Sprite
	@mkdir -p $(OBJS_PATH)Texture
	@mkdir -p $(OBJS_PATH)Shape

clean:
	@rm -f $(OBJS)
	@rm -f $(NAME)

re: clean all

.PHONY: all clean re odir
