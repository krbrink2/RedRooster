CC = g++
CFLAGS = -g -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable
TARGET = RedRooster
OBJS = Game.o GameState.o
HEADERS =  Game.h GameState.h


default: $(TARGET)

# ---- Mine ----

$(TARGET): main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

main.o: Globals.h
	$(CC) -c main.cpp $(CFLAGS)

Game.o: GameState.h
	$(CC) -c Game.cpp $(CFLAGS)

GameState.o:
	$(CC) -c GameState.cpp $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o *~
