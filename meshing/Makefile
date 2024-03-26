OFILES = mesh-demo.o problem-spec.o xmalloc.o mesh-to-eps.o triangle.o
TARGET = mesh-demo
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@ $(LIBS)
		
clean:
		rm -f $(OFILES) $(TARGET)

mesh-demo.o: mesh-demo.c problem-spec.h mesh-to-eps.h mesh.h
problem-spec.o: problem-spec.c array.h xmalloc.h problem-spec.h
xmalloc.o: xmalloc.c xmalloc.h
mesh-to-eps.o: mesh-to-eps.c mesh-to-eps.h mesh.h problem-spec.h
triangle.o: triangle.c triangle.h