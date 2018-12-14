CC = gcc

ST_LIB = -lGL -lGLU -lglut -lm
LIB = -lMKZ

LLIB = libMKZ.a
LLIBDIR = lib

ODIR = obj
SRCDIR = src
HEADDIR = include


CFLAGS = -I$(HEADDIR) -Llib $(LIB) $(ST_LIB) 

_OBJ = main.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

main: $(LLIBDIR)/$(LLIB) $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) 

$(LLIBDIR)/$(LLIB):
	make -C lib/MKZ
	
$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	make -C lib/MKZ clean
	rm obj/* 
	rm main
	