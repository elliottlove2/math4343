OFILES = pme.o xmalloc.o problem-spec.o
TARGET = pme
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@
		
clean:
		rm -f $(OFILES) $(TARGET)

pme.o: pme.c problem-spec.h
xmalloc.o: xmalloc.c xmalloc.h
problem-spec.o: problem-spec.c problem-spec.h