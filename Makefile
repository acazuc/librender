NAME = librender.a

CC = g++

ARCH =

AR = gcc-ar

ARFLAGS =

RANLIB = gcc-ranlib

RANLIBFLAGS =

CLFAGS = -std=c++14 -g -Wall -Wextra -O3 -pipe

INCLUDES_PATH = -I src
INCLUDES_PATH+= -I lib
INCLUDES_PATH+= -I lib/glfw/include
INCLUDES_PATH+= -I lib/freetype/include
INCLUDES_PATH+= -I lib/glad/include

SRCS_PATH = src/

SRCS_NAME = Color.cpp \
	    Draw.cpp \
	    Text/Text.cpp \
	    Text/TextEntry.cpp \
	    Text/TextBatch.cpp \
	    Text/TextBatchEntry.cpp \
	    Text/TextTessellator.cpp \
	    Font/FontModel.cpp \
	    Font/Font.cpp \
	    Font/Glyph.cpp \
	    Shader/FragmentShader.cpp \
	    Shader/VertexShader.cpp \
	    Shader/Program.cpp \
	    Shader/VertexBuffer.cpp \
	    Shader/ProgramLocation.cpp \
	    Shader/GeometryShader.cpp \
	    Shader/Shader.cpp \
	    Shader/FrameBuffer.cpp \
	    Shader/RenderBuffer.cpp \
	    Shader/VertexArray.cpp \
	    Shader/Sprite/ShaderSprite.cpp \
	    Shader/Sprite/ShaderSpriteEntry.cpp \
	    Shader/Sprite/ShaderSpriteBatch.cpp \
	    Shader/Sprite/ShaderSpriteBatchEntry.cpp \
	    Shader/Sprite/ShaderSpriteTessellator.cpp \
	    Shader/Text/ShaderText.cpp \
	    Shader/Text/ShaderTextEntry.cpp \
	    Shader/Text/ShaderTextBatch.cpp \
	    Shader/Text/ShaderTextBatchEntry.cpp \
	    Window/EventsManager.cpp \
	    Window/Window.cpp \
	    Window/Monitor.cpp \
	    Window/VideoMode.cpp \
	    Sprite/Sprite.cpp \
	    Sprite/SpriteEntry.cpp \
	    Sprite/SpriteBatch.cpp \
	    Sprite/SpriteBatchEntry.cpp \
	    Sprite/SpriteTessellator.cpp \
	    Texture/Texture.cpp \
	    Texture/TexturePacker.cpp \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.opp)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(NAME)

$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	@$(AR) -rc $(ARFLAGS) $(NAME) $(OBJS)
	@$(RANLIB) $(RANLIBFLAGS) $(NAME)

$(OBJS_PATH)%.opp: $(SRCS_PATH)%.cpp
	@echo " - Compiling $<"
	@$(CC) $(ARCH) $(CFLAGS) -o $@ -c $< $(INCLUDES_PATH)

odir:
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)Window
	@mkdir -p $(OBJS_PATH)Shader
	@mkdir -p $(OBJS_PATH)Shader/Sprite
	@mkdir -p $(OBJS_PATH)Shader/Text
	@mkdir -p $(OBJS_PATH)Text
	@mkdir -p $(OBJS_PATH)Font
	@mkdir -p $(OBJS_PATH)Sprite
	@mkdir -p $(OBJS_PATH)Vec
	@mkdir -p $(OBJS_PATH)Mat
	@mkdir -p $(OBJS_PATH)Texture

clean:
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning lib"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
