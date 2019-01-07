CC = gcc

ST_LIB = -lGL -lGLU -lglut -lm
LIB = -lMKZ
LIBD = -lMKZDebug

LLIB = libMKZ.a
DLLIB = libMKZDebug.a
LLIBDIR = lib

ODIR = obj
SRCDIR = src
HEADDIR = include


CFLAGS = -I$(HEADDIR) -Llib $(LIB) $(ST_LIB) -O3 
DFLAGS = -I$(HEADDIR) -Llib $(LIBD) $(ST_LIB) -g

_OBJ = main.o objects.o io.o KG.o
_OBJ_D = main_debug.o objects_debug.o io_debug.o KG_debug.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ_D = $(patsubst %,$(ODIR)/%,$(_OBJ_D))

all: main
debug: main_debug
 
main: $(LLIBDIR)/$(LLIB) $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) 

main_debug: $(LLIBDIR)/$(DLLIB) $(OBJ_D)
	$(CC) -o $@ $(OBJ_D) $(DFLAGS) 

$(LLIBDIR)/$(LLIB):
	make -C lib/MKZ
	
$(LLIBDIR)/$(DLLIB):
	make -C lib/MKZ debug
	
$(ODIR)/%_debug.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(DFLAGS)	
	
$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	make -C lib/MKZ clean
	rm obj/* 
	rm main
	rm main_debug