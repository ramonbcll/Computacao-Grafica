CXX			:= g++
CXX_FLAGS	:= -g -std=c++17

SRC			:= src
INCLUDE		:= ./include
LIB			:= ./lib

LIBRARIES	:= -lglfw3dll -lfreeglut -lopengl32 -lglu32
EXECUTABLE	:= main

all:./$(EXECUTABLE)

run: all
	./$(EXECUTABLE)

$(EXECUTABLE):$(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)