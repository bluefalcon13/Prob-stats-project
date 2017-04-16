IDIR=include
CC=gcc
CFLAGS=-I $(IDIR) -fopenmp

SRCDIR=src

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = osmo_a5.o
OBJ = $(patsubst %,$(SRCDIR)/%,$(_OBJ))


$(SRCDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gen_initstates: gen_initstates.o $(OBJ)
	$(CC) -c -o gen_initstates.o gen_initstates.c $(CFLAGS)
	$(CC) -o $@ $^ $(CFLAGS)
    
.PHONY: clean

clean:
	rm -f $(SRCDIR)/*.o *~
