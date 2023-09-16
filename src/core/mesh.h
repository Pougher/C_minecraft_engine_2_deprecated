#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "mesh_attribute.h"

#include "../common/log.h"

typedef struct {
    // a pointer to the vertex mesh in the mesh
    float *vertices;

    // the number of elements in the vertex mesh
    size_t vertices_length;

    // the maximum capacity of the vertex mesh
    size_t vertices_cap;

    // the number of indices in a mesh
    size_t indices;

    // the number of attributes the mesh has
    uint8_t attribute_count;

    // the attributes within the buffer
    MeshAttribute *attributes;

    // the size of the attributes in total
    size_t attribute_size;

    // the vao of the mesh
    unsigned int vao;

    // the vbo of the mesh
    unsigned int vbo;
} Mesh;

// Creates a new mesh
Mesh *mesh_new(void);

// reserves space for the mesh's data
void mesh_reserve(Mesh*, size_t);

// Adds vertices to the vertex mesh
void mesh_add_vertices(Mesh*, float*, size_t, size_t);

// computes the vao and vbo for the mesh
void mesh_compute_buffers(Mesh*);

// renders mesh to the opengl context
void mesh_render(Mesh*);

// prints information about the mesh to stdout
void mesh_stats(Mesh*);

// adds an attribute to the meshs' list of attributes, which are then used when
// generating the vao
void mesh_add_attribute(Mesh*, MeshAttribute);

// dumps the mesh attributes to stdout
void mesh_dump_attributes(Mesh*);

// frees all data allocated to the mesh
void mesh_free(Mesh*);

#endif
