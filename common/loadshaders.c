#include "loadshaders.h"

const char* _loadshaderfile(char* filename){
    char* file = 0;
    long length = 0;
    FILE * f = fopen (filename, "rb");

    if (f)
    {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    file = malloc (length+1);
    if (file)
    {
        fread (file, 1, length, f);
    }
    fclose (f);
    }
    file[length] = '\0';

    return file;
}

GLuint loadshaders(char* vertexfilepath,char* fragmentfilepath){

    const char* vertex_shader = _loadshaderfile(vertexfilepath);
    const char* fragment_shader = _loadshaderfile(fragmentfilepath);
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    glDetachShader(shader_program, vs);
	glDetachShader(shader_program, fs);
	
	glDeleteShader(vs);
	glDeleteShader(fs);

    return shader_program;
}