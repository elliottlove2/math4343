OFILES = xmalloc.o xmalloc-demo-2.o
TARGET = xmalloc-demo-2
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@

clean:
		rm -f $(OFILES) $(TARGET)

xmalloc.o: xmalloc.c xmalloc.h
xmalloc-demo-2.o: xmalloc-demo-2.c xmalloc.h

