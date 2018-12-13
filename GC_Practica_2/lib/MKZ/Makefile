CC = gcc
LIBC = ar rcs

LIB = -lGL -lGLU -lglut -lm

INCLUDEDIR=include

_OBJ=MKZ_Arithmetic.o MKZ_Datastruct.o MKZ_Draw.o MKZ_Geometry.o MKZ.o MKZ_Scene.o MKZ_Test.o MKZ_Transform.o MKZ_WindowManager.o
OBJDIR=obj
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

SRCDIR=src

FLAGS=-I$(INCLUDEDIR)

all: libMKZ.a

libMKZ.a: $(OBJ)
	$(LIBC) ../$@ $^
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(FLAGS) $(LIB)

clean:
	rm obj/*
	rm ../libMKZ.a