#taken from tutorial @ http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =../include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=-lm -lncurses


_DEPS = journal.h journal_errors.h journal_display.h journal_io.h journal_util.h journal_debug.h journal_buffer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = journal.o journal_errors.o journal_display.o journal_io.o journal_util.o journal_debug.o journal_buffer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

journal: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	ctags -e -R ~/programming/journal/ -h .c.h

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
