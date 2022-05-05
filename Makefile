#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -I /usr/include/SDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = a.out

all: object npc texture map game main

#This is the target that compiles our executable

object	:
	g++ -c -Wall -fpic Object.cpp

npc :
	g++ -c -Wall -fpic NPC.cpp

texture : 
	g++ -c -Wall -fpic TM.cpp

map	:
	g++ -c -Wall -fpic Map.cpp

game : 
	g++ -c -Wall -fpic Game.cpp

main : $(OBJS)
	$(CC) Object.o TM.o Map.o Game.o NPC.o $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
