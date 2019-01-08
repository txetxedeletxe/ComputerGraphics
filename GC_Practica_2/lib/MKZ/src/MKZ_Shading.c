#include <GL/glew.h>
#include <GL/gl.h>

#include <string.h>

#include <stdio.h>

#include "MKZ_Shading.h"
#include "MKZ_Io.h"
#include "MKZ_Definitions.h"

//Shaders
//Vertex
GLuint vs_default;
GLuint fs_default;

//Programs
GLuint p_default;


void MKZ_SHADING_init(){


	int error = glewInit();

	if (error == GLEW_OK){
		fprintf(stdout,"GLEW available\n");
	}
	else{
		fprintf(stderr,"Error: %s\n",glewGetErrorString(error));
	}

	int strLen;
	char * sourceStr;
	char bufferStr[200];

	//Create shaders

	vs_default = glCreateShader(GL_VERTEX_SHADER);
	fs_default = glCreateShader(GL_FRAGMENT_SHADER);

	//Attach sources
	strcpy(bufferStr,shader_directory);
	strcat(bufferStr,"/vs_default.glsl");

	strLen = MKZ_IO_Readfile(bufferStr,&sourceStr);

	const char * vs_default_source = sourceStr;

	glShaderSource(vs_default, 1, &vs_default_source, &strLen);


	strcpy(bufferStr,shader_directory);
	strcat(bufferStr,"/fs_default.glsl");

	strLen = MKZ_IO_Readfile(bufferStr,&sourceStr);

	const char * fs_default_source = sourceStr;

	glShaderSource(fs_default, 1, &fs_default_source, &strLen);


	//Compile shaders
	glCompileShader(vs_default);
	glCompileShader(fs_default);


	//Create programs
	p_default = glCreateProgram();


	//Attach shaders
	glAttachShader(p_default, vs_default);
	glAttachShader(p_default, fs_default);


	//Link programs
	glLinkProgram(p_default);

	glUseProgram(p_default);

}

void MKZ_SHADING_use_model(int model){

	switch (model){

	case MKZ_SHADING_UNLIT:
	default:
		glUseProgram(p_default);
	}
}
