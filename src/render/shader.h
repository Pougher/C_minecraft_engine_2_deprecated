#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../common/log.h"
#include "../common/fileio.h"

#define GL_UNIFORM_LOCATION glGetUniformLocation(shader->id, name)

typedef struct {
    // the ID of the shader
    unsigned int id;
} Shader;

// Creates a new Shader object allocated on the heap, meaning it must
// be freed later. It automatically generates a shader ID that can be used by
// OpenGL while rendering.
Shader* shader_new(char*, char*);

// Tells OpenGL to bind a shader
void shader_use(Shader*);

// Destroys the OpenGL program ID and then frees the data allocated to the
// shader
void shader_free(Shader*);

// SENDING DATA TO SHADERS

// Sends a boolean to the provided shader
void shader_setbool(Shader*, const char*, bool);

// Sends an integer to the provided shader
void shader_setint(Shader*, const char*, int);

// Sends a float to the provided shader
void shader_setfloat(Shader*, const char*, float);

// Sends a vec3 to the provided shader
void shader_setvec3(Shader*, const char*, vec3);

// Sends a mat4 to the provided shader
void shader_setmat4(Shader*, const char*, mat4);

#endif
