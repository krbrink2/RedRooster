# This is a qmake project file.
# Use
#   qmake RedRooster
# to generate a Makefile
CONFIG += debug
QMAKE_CXXFLAGS += -std=c++11 -g -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

HEADERS += inc/*.h  
SOURCES += src/*.cpp
INCLUDEPATH += src inc
OBJECTS_DIR = obj
