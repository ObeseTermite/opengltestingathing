#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <cglm/cglm.h>

#include "common/loadshaders.h"

#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / m_PI)

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 512;
int g_gl_height = 512;

// a call-back function
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
  g_gl_width = width;
  g_gl_height = height;
  
  /* update any perspective matrices used here */
}

int main(){
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    } 

    
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(g_gl_width, g_gl_height, "Rocktangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
                                    
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    /* OTHER STUFF GOES HERE NEXT */
    float points[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f,  0.0f
    };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    float colors[] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    };

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 36*3 * sizeof(float), vertices, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, 36*3 * sizeof(float), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLuint shader_program = loadshaders("test_vs.glsl","test_fs.glsl");

    vec3 pos = {0,0,-3};

    vec3 rotation = {0,0,0};

    float speed = 3;
    float rotation_speed = 100;

    double previous_seconds = glfwGetTime();
     

    while(!glfwWindowShouldClose(window)) {
        double current_seconds = glfwGetTime();
        double deltatime = current_seconds - previous_seconds;
        previous_seconds = current_seconds;
        printf("framerate: %d\n",(int)(1/deltatime));

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
            pos[0]+=speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)) {
            pos[0]-=speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
            pos[2]+=speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)) {
            pos[2]-=speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q)) {
            pos[1]+=speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E)) {
            pos[1]-=speed*deltatime;
        }

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
            rotation[1]-=rotation_speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
            rotation[1]+=rotation_speed*deltatime;
        }

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
            rotation[0]+=rotation_speed*deltatime;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
            rotation[0]-=rotation_speed*deltatime;
        }

        mat4 model;

        glm_translate_make(model,(vec3){0,0,0});
        glm_rotate(model, degToRad(clock()/1000), (vec3){0.0, 1.0, 0.0});
        glm_scale(model, (vec3){1, 1, 1}); 

        mat4 view;
        
        glm_rotate_make(view,degToRad(-rotation[0]),(vec3){1,0,0});
        glm_rotate(view,degToRad(rotation[2]),(vec3){0,0,1});
        glm_rotate(view,degToRad(rotation[1]),(vec3){0,1,0});
        glm_translate(view, pos);
        
    
        mat4 projection;

        glm_perspective(degToRad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f,projection);

        // wipe the drawing surface clear
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSetWindowSizeCallback(window, glfw_window_size_callback);
        glViewport(0, 0, g_gl_width, g_gl_height);

        glUseProgram(shader_program);

        unsigned int modelLoc = glGetUniformLocation(shader_program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);
        unsigned int viewLoc = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)view);
        unsigned int projectionLoc = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float*)projection);

        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0,36);
        // update other events like input handling 
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }   

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}