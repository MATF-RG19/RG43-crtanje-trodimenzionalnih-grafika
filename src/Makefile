PROGRAM = graph
CC      = g++
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o draw.o camera.o utility.o plot.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o $(LDLIBS)

draw.o: draw.cpp utility.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) -c $< $(LDLIBS)

camera.o: draw.cpp utility.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) -c $< $(LDLIBS)

utility.o: utility.cpp
	$(CC) $(LDFLAGS) -o $(PROGRAM) -c $< $(LDLIBS)

plot.o: plot.cpp
	$(CC) $(LDFLAGS) -o $(PROGRAM) -c $< $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
