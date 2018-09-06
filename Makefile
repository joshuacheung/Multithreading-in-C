CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g -lpthread
OBJECTS = increment.o

.PHONY:	all
all:	increment

increment:	$(OBJECTS)
	$(CC)	$(CFLAGS)	$(OBJECTS) -o increment -lm

increment.o: increment.c
	$(CC)	$(CFLAGS)	-g -c increment.c -lm

.PHONY:	clean
clean:
	-rm	-f	$(OBJECTS)	increment
