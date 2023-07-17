#ifndef LOADSHADERS_H_
#define LOADSHADERS_H_

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

const char* _loadshaderfile(char* filename);

GLuint loadshaders(char* vertexfilepath,char* fragmentfilepath);

#endif