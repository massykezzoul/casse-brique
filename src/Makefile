#################################################################################
#
#
# Informations: :
#
#− BECHEV Boyan <boyan.b.2012@feg.bg>
#  FOURNIER Romain <>
#
#
#− Casse-brique
#
#
#− Programmation avancee
#################################################################################

#Variables:

CC	 = g++
FLAGS    = -Wall -lncurses
PROG_NAME= casse-brique
SOURCE	 = Body.cpp LinkedList.cpp main.cpp window.cpp brick.cpp player.cpp Terrain.cpp ball.cpp raquette.cpp
VERSION  = 'eval\ date\ +%d_%m_%Y'

#Cibles:

#usuelles
all : $(PROG_NAME)

#compilation

Body.o       : Body.cpp
	@$(CC) -c $<  $(FLAGS)
LinkedList.o : LinkedList.cpp
	@$(CC) -c $<  $(FLAGS)
main.o       : main.cpp
	@$(CC) -c $<  $(FLAGS)
window.o     : window.cpp
	@$(CC) -c $<  $(FLAGS)
brick.o      : brick.cpp
	@$(CC) -c $<  $(FLAGS)
player.o     : player.cpp
	@$(CC) -c $<  $(FLAGS)
Terrain.o    : Terrain.cpp
	@$(CC) -c $<  $(FLAGS)
ball.o		 : ball.cpp
	@$(CC) -c $<  $(FLAGS)
raquette.o 	 : raquette.cpp
	@$(CC) -c $<  $(FLAGS)


$(PROG_NAME) : $(SOURCE:.cpp=.o)
	@$(CC) $^ -o $@ $(FLAGS) && echo 'Compilation OK' || 'Fail on Compilation'


.PHONY: clean mrproper

# Delete *.o files 
clean :
	@rm $(SOURCE:.cpp=.o) -rvf

# Delete executable
mrproper: clean
	@rm $(PROG_NAME) -v