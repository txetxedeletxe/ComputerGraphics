CC = gcc
LIBC = ar rcs

LIB = -lGL -lGLU -lglut -lm

INCLUDEDIR=interface

_OBJ=MKZEngine.o WindowManager.o Draw.o DrawTools.o Utilities.o Datastruct.o Transform.o
OBJDIR=obj
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

SRCDIR=src

FLAGS=-I$(INCLUDEDIR)

all: libMKZengine.a

libMKZengine.a: $(OBJ)
	$(LIBC) ../$@ $^
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(FLAGS) $(LIB)

clean:
	rm obj/*
	rm ../libMKZengine.a