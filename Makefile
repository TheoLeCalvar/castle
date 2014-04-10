EXT = cpp
CXX = g++

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXXFLAGS = -g
LDFLAGS = -lSOIL -lglew -lglfw3 -F/usr/local/lib -framework OpenGL -framework ApplicationServices -framework QtCore -framework QtXml
endif

ifeq ($(UNAME), Linux)
CXXFLAGS = -Wall -std=c++0x
LDFLAGS = -lSOIL -lGL -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lQtCore -lQtXml
endif

OBJDIR = obj
EXEC = exe
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
