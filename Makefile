CC=gcc
CFLAGS=-O2 -g -Wall
OPTFLAGS=-O3 -g -Wall
OBJS=driver.o kernel.o rdtsc.o

all:	sgemm

sgemm:	$(OBJS)
	$(CC) -o $@ $^

kernel.o: kernel.c
	$(CC) $(OPTFLAGS) -D $(OPT) -c $< -o $@

clean:
	rm -rf $(OBJS) sgemm
