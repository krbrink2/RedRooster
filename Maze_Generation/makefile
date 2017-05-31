CC = gcc

COMPILER_FLAGS = -Wall -std=c99 -I/opt/local/include
LINKER_FLAGS = -lm -L/opt/local/lib

DEPS = MazeGeneration.c Queue.c

BUILD_FILES = GenerateMaze

.PHONY: build 
build:
	make GenerateMaze

GenerateMaze: $(DEPS)
	$(CC) $(DEPS) -o GenerateMaze $(COMPILER_FLAGS) $(LINKER_FLAGS)

.PHONY: clean
clean:
	rm -f *.o $(BUILD_FILES)