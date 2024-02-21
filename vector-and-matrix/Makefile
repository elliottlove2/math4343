OFILES = orthogonal.o xmalloc.o
TARGET = orthogonal
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@
		
clean:
		rm -f $(OFILES) $(TARGET)

orthogonal.o: orthogonal.c array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h