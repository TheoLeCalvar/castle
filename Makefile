EXT = cpp
CXX = g++

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXXFLAGS = -g
LDFLAGS = -framework OpenGL -framework ApplicationServices -lSOIL -lglew -lglfw3
OBJDIR = obj/darwin
EXEC = exe-darwin
endif

ifeq ($(UNAME), Linux)
CXXFLAGS = -Wall -std=c++0x
LDFLAGS = -lSOIL -lGL -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi
OBJDIR = obj/linux
EXEC = exe-linux
endif
 
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))
 
all: $(EXEC)
 
$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)
 
$(OBJDIR)/%.o: %.$(EXT)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

run: $(EXEC)
	./$(EXEC)
 
clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f $(EXEC)
