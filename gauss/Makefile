OFILES = gauss-quad-demo.c gauss-quad.c xmalloc.o
TARGET = demo
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@ $(LIBS)
		
clean:
		rm -f $(OFILES) $(TARGET)

gauss-quad-demo.o: gauss-quad-demo.c gauss-quad.h array.h xmalloc.h
gauss-quad.o: gauss-quad.c gauss-quad.h
xmalloc.o: xmalloc.c xmalloc.h