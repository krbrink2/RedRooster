CC = g++
CFLAGS = -g -Wall -Werror -Wextra # -Wno-unused-parameter -Wno-unused-variable
TARGET = RedRooster
OBJS = main.o
HEADERS =  


default: $(TARGET)

# ---- Mine ----

$(TARGET): main.o $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp $(HEADERS)
	$(CC) -c main.cpp $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o *~
