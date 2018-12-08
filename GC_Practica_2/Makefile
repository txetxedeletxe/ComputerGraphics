CC = gcc

LIB = -lGL -lGLU -lglut -lm -lMKZengine

LLIB = libMKZengine.a
LLIBDIR = lib

ODIR = obj
SRCDIR = src
HEADDIR = include


CFLAGS = -I$(HEADDIR) -Llib

_OBJ = display.o io.o load_obj.o main.o transform.o definitions.o utilities.o camera.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

main: $(LLIBDIR)/$(LLIB) $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIB)

$(LLIBDIR)/$(LLIB):
	make -C lib/MKZ
	
$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm obj/* 
	rm main
	make -C lib/MKZ clean