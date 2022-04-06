CC=gcc
CFLAGS=-O2 -g -Wall 
OBJS=driver.o kernel.o rdtsc.o

all:	Sujet11

Sujet11: $(OBJS)
	$(CC) -o $@ $^ -lm

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c  $< -o $@ -lm

clean:
	rm -rf $(OBJS) Sujet11
	
	
