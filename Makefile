CC = g++
CFLAGS = -std=c++11 -g -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable
TARGET = RedRooster
OBJS = Game.o GameState.o GameplayState.o Map.o Globals.h Mob.o MobController.o Obstacle.o PlayerController.o
#HEADERS =  Game.h GameState.h


default: $(TARGET)

# ---- Mine ----

$(TARGET): main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Globals.h GameplayState.h
	$(CC) -c main.cpp $(CFLAGS)

Game.o: Game.cpp Game.h GameState.h
	$(CC) -c Game.cpp $(CFLAGS)

GameplayState.o: GameplayState.cpp GameplayState.h GameState.h Map.h 
	$(CC) -c GameplayState.cpp $(CFLAGS)

GameState.o: GameState.cpp GameState.h Mob.h
	$(CC) -c GameState.cpp $(CFLAGS)

Map.o: Map.cpp Map.h Mob.h Obstacle.h PlayerController.h
	$(CC) -c Map.cpp $(CFLAGS)

Mob.o: Mob.cpp Mob.h
	$(CC) -c Mob.cpp $(CFLAGS)

MobController.o: MobController.cpp MobController.h Mob.h
	$(CC) -c MobController.cpp $(CFLAGS)

Obstacle.o: Obstacle.cpp Obstacle.h
	$(CC) -c Obstacle.cpp $(CFLAGS)

PlayerController.o: PlayerController.cpp PlayerController.h MobController.h
	$(CC) -c PlayerController.cpp $(CFLAGS)


clean:
	$(RM) $(TARGET) *.o *~
