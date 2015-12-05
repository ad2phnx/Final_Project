# Makefile for Final Project [Box of Fortune]

OBJS = main.o game.o player.o word.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

BoF : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o BoF

main.o : main.cpp game.h
	$(CC) $(CFLAGS) main.cpp

game.o : game.h game.cpp word.h player.h
	$(CC) $(CFLAGS) game.cpp

player.o : player.h player.cpp
	$(CC) $(CFLAGS) player.cpp

word.o : word.h word.cpp
	$(CC) $(CFLAGS) word.cpp

clean:
	\rm *.o *~ BoF

tar:
	tar cfv BoF.tar main.cpp
