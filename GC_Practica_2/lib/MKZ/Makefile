CC = gcc
LIBC = ar rcs

LIB = -lGL -lGLU -lglut -lm -lGLEW
INCLUDEDIR=include

_OBJ=MKZ_Arithmetic.o MKZ_Datastruct.o MKZ_Draw.o MKZ_Geometry.o MKZ.o MKZ_Scene.o  MKZ_Transform.o MKZ_WindowManager.o MKZ_Io.o MKZ_Objects.o MKZ_Lighting.o MKZ_Shading.o
_OBJ_D=MKZ_Arithmetic_debug.o MKZ_Datastruct_debug.o MKZ_Draw_debug.o MKZ_Geometry_debug.o MKZ_debug.o MKZ_Scene_debug.o  MKZ_Transform_debug.o MKZ_WindowManager_debug.o MKZ_Io_debug.o MKZ_Objects_debug.o MKZ_Lighting_debug.o MKZ_Shading_debug.o
OBJDIR=obj

OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
OBJ_D = $(patsubst %,$(OBJDIR)/%,$(_OBJ_D))

SRCDIR=src

FLAGS=-I$(INCLUDEDIR) -O3 $(LIB) 
DFLAGS=-I$(INCLUDEDIR) -g $(LIB) 
 
all: libMKZ.a 
debug: libMKZDebug.a

libMKZ.a: $(OBJ) 
	$(LIBC) ../$@ $^
	
libMKZDebug.a: $(OBJ_D) 
	$(LIBC) ../$@ $^
	
$(OBJDIR)/%_debug.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(DFLAGS) 
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ $(FLAGS) 



clean:
	rm obj/*
	rm ../libMKZ.a
	rm ../libMKZDebug.a