IDIR = ../include
CC = gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = -I$(IDIR) $(shell $(PKGCONFIG) gtk+-2.0 --cflags)
LIBS = $(shell $(PKGCONFIG) gtk+-2.0 --libs)

ODIR=obj

_DEPS = callbacks.h menus.h windows.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = grafico.o callbacks.o menus.o windows.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: grafico

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

grafico: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
