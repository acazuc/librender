NAME = librender.a

CC = g++

ARCH =

AR = gcc-ar

ARFLAGS =

RANLIB = gcc-ranlib

RANLIBFLAGS =

CLFAGS = -std=c++11 -Wall -Wextra -O3 -pipe -fno-rtti

INCLUDES_PATH = -I src
INCLUDES_PATH+= -I lib
INCLUDES_PATH+= -I lib/glfw/include
INCLUDES_PATH+= -I lib/freetype/include
INCLUDES_PATH+= -I lib/glad/include
INCLUDES_PATH+= -I lib/libunicode/include

SRCS_PATH = src/

SRCS_NAME = Color.cpp \
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
	    Context/Context.cpp \
	    Context/OpenGL1/OpenGL1Context.cpp \

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
	@mkdir -p $(OBJS_PATH)Context
	@mkdir -p $(OBJS_PATH)Context/OpenGL1
	@mkdir -p $(OBJS_PATH)Context/OpenGL2

clean:
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning lib"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
