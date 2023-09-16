CC=gcc

CFLAGS = -lm
OBJECTS = ant.o main.o grid.o utils.o parseargs.o parsefile.o


default: link

link: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o a.out

.c.o:
	$(CC) $(CFLAGS) -c -g $<

clean:
	rm -f *.o
