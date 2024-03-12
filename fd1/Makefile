OFILES = heat-explicit.o xmalloc.o problem-spec.o
TARGET = heat-explicit
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@ $(LIBS)
		
clean:
		rm -f $(OFILES) $(TARGET)

heat-explicit.o: heat-explicit.c array.h xmalloc.h problem-spec.h
xmalloc.o: xmalloc.c xmalloc.h
problem-spec.o: problem-spec.c problem-spec.h
