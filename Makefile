#
# basic makefile for coreengine
#
CC = @g++
CFLAGS = -pedantic -Wno-variadic-macros -g -O0 -I/usr/include -I SFML/include -DLINUXBUILD -DCOREENGINE
LDFLAGS= -L /usr/lib 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES=$(wildcard *.cpp) $(wildcard filter/*.cpp) $(wildcard emitters/*.cpp) $(wildcard actions/*.cpp) $(wildcard initializers/*.cpp) $(wildcard zones/*.cpp)  
OBJECTS=$(patsubst %.cpp, obj/%.o, $(SOURCES))
TARGET=coengine

all: header $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "-------------------------------------------------------------------"
	@echo "Linking target..."
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@
	@echo "Done."

clean:
	@echo "Clear old objects"
	-@rm obj/*.o

header:
	@echo "###################################################################"
	@echo " CORE-ENGINE"
	@echo "###################################################################"
	@(mkdir -p obj)
	@(mkdir -p obj/emitters)
	@(mkdir -p obj/initializers)
	@(mkdir -p obj/actions)
	@(mkdir -p obj/zones)
	@(mkdir -p obj/filter)

obj/%.o: %.cpp
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@



