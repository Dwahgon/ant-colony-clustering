CC=gcc

CFLAGS = -lm
OBJECTS = ant.o main.o grid.o  utils.o


default: link

link: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o a.out

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
