CC=gcc
CFLAGS=-Wall -ansi
RUSTC=rustc

APP=ffi1
PROGNAME=$(APP)
LIBNAME=lib$(APP).a

RUST_SRC=$(APP).rs
LIB_SRC=$(APP).c
OBJ_FILE=$(APP).o

# Vychozi pravidlo pro vytvoreni vysledne spustitelne aplikace.
all:	$(LIBNAME) $(PROGNAME)

# Pravidlo pro slinkovani vsech objektovych souboru a vytvoreni
# vysledne spustitelne aplikace.
$(PROGNAME):	$(RUST_SRC) $(LIBNAME)
	$(RUSTC) -L . $<

# Pravidlo pro preklad knihovny
$(LIBNAME):	$(OBJ_FILE)
	ar rcs $(LIBNAME) $<

%.o:    %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.a
	rm -f $(PROGNAME)

run:
	./$(APP)
