#################################################################################
#
#
# Informations: :
#
#− BECHEV Boyan <boyan.b.2012@feg.bg>
#  FOURNIER Romain <>
#  KEZZOUL Massili < massili.kezzoul@etu.umontpellier.fr >
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
SOURCE	 = main.cpp window.cpp brick.cpp player.cpp ball.cpp raquette.cpp menu.cpp boutton/boutton.cpp
VERSION  = 'eval\ date\ +%d_%m_%Y'

#usuelles
all : $(PROG_NAME)

#compilation

main.o       : main.cpp
	@$(CC) -c $<  $(FLAGS)
window.o     : window.cpp
	@$(CC) -c $<  $(FLAGS)
brick.o      : brick.cpp
	@$(CC) -c $<  $(FLAGS)
player.o     : player.cpp
	@$(CC) -c $<  $(FLAGS)
ball.o		 : ball.cpp
	@$(CC) -c $<  $(FLAGS)
raquette.o 	 : raquette.cpp
	@$(CC) -c $<  $(FLAGS)
menu.o: menu.cpp
	@$(CC) -c $<  $(FLAGS)
boutton/boutton.o: boutton/boutton.cpp
	@$(CC) -o boutton/boutton.o -c $<  $(FLAGS)

$(PROG_NAME) : $(SOURCE:.cpp=.o)
	@$(CC) $^ -o $@ $(FLAGS) && echo 'Compilation OK' || 'Fail on Compilation'


.PHONY: clean mrproper

# Delete *.o files 
clean :
	@rm $(SOURCE:.cpp=.o) -rvf

# Delete executable
mrproper: clean
	@rm $(PROG_NAME) -v