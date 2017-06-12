CC = g++
CFLAGS = -std=c++11 -g -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable
TARGET = RedRooster
OBJS = Game.o GameState.o GameplayState.o Map.o Globals.h Mob.o Obstacle.o
#HEADERS =  Game.h GameState.h


default: $(TARGET)

# ---- Mine ----

$(TARGET): main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

main.o: Globals.h GameplayState.h
	$(CC) -c main.cpp $(CFLAGS)

Game.o: GameState.h
	$(CC) -c Game.cpp $(CFLAGS)

GameplayState.o: GameState.h
	$(CC) -c GameplayState.cpp $(CFLAGS)

GameState.o: Mob.h
	$(CC) -c GameState.cpp $(CFLAGS)

Map.o: Mob.h Obstacle.h PlayerController.h
	$(CC) -c Map.cpp $(CFLAGS)

Mob.o:
	$(CC) -c Mob.cpp $(CFLAGS)

MobController.o: Mob.h
	$(CC) -c MobController.cpp $(CFLAGS)

Obstacle.o:
	$(CC) -c Obstacle.cpp $(CFLAGS)

PlayerController.o: MobController.h
	$(CC) -c PlayerController.cpp $(CFLAGS)


clean:
	$(RM) $(TARGET) *.o *~
