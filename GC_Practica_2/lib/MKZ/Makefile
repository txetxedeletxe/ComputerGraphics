CC = gcc
LIBC = ar rcs

LIB = -lGL -lGLU -lglut -lm

INCLUDEDIR=include

_OBJ=MKZ_Arithmetic.o MKZ_Datastruct.o MKZ_Draw.o MKZ_Geometry.o MKZ.o MKZ_Scene.o  MKZ_Transform.o MKZ_WindowManager.o MKZ_Io.o MKZ_Objects.o
_OBJ_D=MKZ_Arithmetic_debug.o MKZ_Datastruct_debug.o MKZ_Draw_debug.o MKZ_Geometry_debug.o MKZ_debug.o MKZ_Scene_debug.o  MKZ_Transform_debug.o MKZ_WindowManager_debug.o MKZ_Io_debug.o MKZ_Objects_debug.o
OBJDIR=obj

OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
OBJ_D = $(patsubst %,$(OBJDIR)/%,$(_OBJ_D))

SRCDIR=src

FLAGS=-I$(INCLUDEDIR) -O3 
DFLAGS=-I$(INCLUDEDIR) -g
 
all: libMKZ.a
debug: libMKZDebug.a

libMKZ.a: $(OBJ)
	$(LIBC) ../$@ $^
	
libMKZDebug.a: $(OBJ_D)
	$(LIBC) ../$@ $^
	
$(OBJDIR)/%_debug.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(DFLAGS) $(LIB)	
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(FLAGS) $(LIB)

clean:
	rm obj/*
	rm ../libMKZ.a
	rm ../libMKZDebug.a