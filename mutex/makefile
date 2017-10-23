CC = gcc
CFLAGS = -Wall -g

mutex: mutex.o
	$(CC) -o mutex mutex.o -lpthread

mutex.o: mutex.c
	$(CC) $(CFLAGS) -c -o mutex.o mutex.c
