CC = gcc

LIB = -lGL -lGLU -lglut -lm

ODIR = obj
SRCDIR = src
HEADDIR = include


CFLAGS = -I$(HEADDIR)

_OBJ = display.o io.o load_obj.o main.o transform.o definitions.o utilities.o camera.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm obj/* main