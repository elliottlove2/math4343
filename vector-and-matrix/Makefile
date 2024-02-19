OFILES = hilbert-matrix.o xmalloc.o
TARGET = hilbert
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@
		
clean:
		rm -f $(OFILES) $(TARGET)

hilbert-matrix.o: hilbert-matrix.c array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h