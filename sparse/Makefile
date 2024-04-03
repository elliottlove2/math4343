OFILES = sparse.o xmalloc.o sparse-test.o
TARGET = sparse-test
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
$(TARGET) : $(OFILES)
		$(CC) $(OFILES) -o $@ $(LIBS)
		
clean:
		rm -f $(OFILES) $(TARGET)

sparse-test.o: sparse-test.c sparse.h array.h xmalloc.h
sparse.o: sparse.c sparse.h array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h