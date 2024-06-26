#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL2
#

#CXX = g++
#CXX = clang++

EXE = paint
IMGUI_DIR = ../
SOURCES = square.cpp
SOURCES += $(IMGUI_DIR)/imgui/imgui.cpp $(IMGUI_DIR)/imgui/imgui_demo.cpp $(IMGUI_DIR)/imgui/imgui_draw.cpp $(IMGUI_DIR)/imgui/imgui_tables.cpp $(IMGUI_DIR)/imgui/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backend/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backend/imgui_impl_opengl3.cpp
SOURCES += $(IMGUI_DIR)/themes/default_theme.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -std=c++11 -I$(IMGUI_DIR)/imgui -I$(IMGUI_DIR)/backend -I$(IMGUI_DIR)/themes -I$(IMGUI_DIR)/icons
CXXFLAGS += -g -Wall -Wformat
SOURCES += 
LIBS =

##---------------------------------------------------------------------
## OPENGL ES
##---------------------------------------------------------------------

## This assumes a GL ES library available in the system, e.g. libGLESv2.so
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_ES2
# LINUX_GL_LIBS = -lGLESv2
## If you're on a Raspberry Pi and want to use the legacy drivers,
## use the following instead:
# LINUX_GL_LIBS = -L/opt/vc/lib -lbrcmGLESv2

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs` -lSDL2_image

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

# ifeq ($(UNAME_S), Darwin) #APPLE
# 	ECHO_MESSAGE = "Mac OS X"
# 	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo `sdl2-config --libs`
# 	LIBS += -L/usr/local/lib -L/opt/local/lib
# 
# 	CXXFLAGS += `sdl2-config --cflags`
# 	CXXFLAGS += -I/usr/local/include -I/opt/local/include
# 	CFLAGS = $(CXXFLAGS)
# endif
# 
# LIBS += -lgdi32 -lopengl32 -lSDL2main -lSDL2 -lSDL2_image

ifeq ($(OS), Windows_NT)
    ECHO_MESSAGE = "MinGW"
    LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2`
	
    CXXFLAGS += `pkg-config --cflags sdl2`
    CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backend/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/themes/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
