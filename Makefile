CC = g++
CFLAGS = -std=c++11 -g -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable
TARGET = RedRooster
OBJS = Boundable.o Game.o GameState.o GameplayState.o Globals.o Map.o Globals.h Mob.o MobController.o Obstacle.o PlayerController.o
#HEADERS =  Game.h GameState.h


default: $(TARGET)

# ---- Mine ----

$(TARGET): main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Globals.h GameplayState.h
	$(CC) -c main.cpp $(CFLAGS)

Boundable.o: Boundable.cpp Boundable.h Globals.h
	$(CC) -c Boundable.cpp $(CFLAGS)

Game.o: Game.cpp Game.h GameState.h Globals.h
	$(CC) -c Game.cpp $(CFLAGS)

GameplayState.o: GameplayState.cpp GameplayState.h GameState.h Map.h Globals.h
	$(CC) -c GameplayState.cpp $(CFLAGS)

GameState.o: GameState.cpp GameState.h Mob.h Globals.h
	$(CC) -c GameState.cpp $(CFLAGS)

Globals.o: Globals.cpp Globals.h
	$(CC) -c Globals.cpp $(CFLAGS)

Map.o: Map.cpp Map.h Mob.h Obstacle.h PlayerController.h Globals.h
	$(CC) -c Map.cpp $(CFLAGS)

Mob.o: Mob.cpp Mob.h Boundable.h Globals.h
	$(CC) -c Mob.cpp $(CFLAGS)

MobController.o: MobController.cpp MobController.h Mob.h Globals.h
	$(CC) -c MobController.cpp $(CFLAGS)

Obstacle.o: Obstacle.cpp Obstacle.h Boundable.h Globals.h
	$(CC) -c Obstacle.cpp $(CFLAGS)

PlayerController.o: PlayerController.cpp PlayerController.h MobController.h Globals.h
	$(CC) -c PlayerController.cpp $(CFLAGS)


clean:
	$(RM) $(TARGET) *.o *~
