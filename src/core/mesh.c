#include "mesh.h"

Mesh *mesh_new(void) {
    Mesh *new_mesh = malloc(sizeof(Mesh));
    new_mesh->vertices = NULL;

    new_mesh->vertices_length = 0;
    new_mesh->vertices_cap = 1;

    new_mesh->indices = 0;

    new_mesh->vao = 0;
    new_mesh->vbo = 0;

    // initialize the meshs' attributes
    new_mesh->attributes = NULL;
    new_mesh->attribute_count = 0;
    new_mesh->attribute_size = 0;

    return new_mesh;
}

void mesh_reserve(Mesh *mesh, size_t cap) {
    mesh->vertices = realloc(mesh->vertices, cap);
    if (mesh->vertices == NULL) {
        log_error("Failed to allocate memory for chunk");
        exit(1);
    }

    mesh->vertices_cap = cap;
}

void mesh_add_data(Mesh *mesh,
    void *verts,
    size_t elem_size,
    size_t len,
    size_t indices) {
    size_t final_length = mesh->vertices_length + len * elem_size;
    if (final_length >= mesh->vertices_cap) {
        while (final_length >= mesh->vertices_cap)
            mesh->vertices_cap *= 2;
        mesh->vertices = realloc(
            mesh->vertices,
            mesh->vertices_cap);
        if (mesh->vertices == NULL) {
            log_error("Failed to allocate mesh space: realloc() failed");
            exit(1);
        }
    }

    // copy the new vertices into the allocated mesh data, offset by its
    // length
    memcpy(
        (char*)mesh->vertices + mesh->vertices_length,
        verts,
        len * elem_size);

    mesh->vertices_length = final_length;
    mesh->indices += indices;
}

void mesh_compute_buffers(Mesh *mesh) {
    // delete the old vao and vbo
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);

    // generate the vao
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    // first, bind the mesh's vao
    glBindVertexArray(mesh->vao);
    // generate the vbo
    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

    // assign the buffer data from the mesh's mesh
    glBufferData(
        GL_ARRAY_BUFFER,
        mesh->vertices_length,
        mesh->vertices,
        GL_STATIC_DRAW);

    // generate vertex attribute pointers
    for (uint8_t i = 0; i < mesh->attribute_count; i++) {
        glVertexAttribPointer(i,
            mesh->attributes[i].size,
            mesh->attributes[i].type,
            GL_FALSE,
            mesh->attribute_size,
            mesh->attributes[i].index);
        glEnableVertexAttribArray(i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh_render(Mesh *mesh) {
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->indices);
}

void mesh_stats(Mesh *mesh) {
    printf("Mesh length: %zu\n"
           "Mesh capacity: %zu\n"
           "Mesh attribute size: %zu\n",
           mesh->vertices_length,
           mesh->vertices_cap,
           mesh->attribute_size);
}

void mesh_add_attribute(Mesh *mesh, MeshAttribute attribute) {
    mesh->attributes = realloc(mesh->attributes,
        sizeof(MeshAttribute) * (mesh->attribute_count + 1));

    memcpy((char*)mesh->attributes +
        (mesh->attribute_count * sizeof(MeshAttribute)),
        (char*)&attribute,
        sizeof(MeshAttribute));

    mesh->attribute_count++;
    mesh->attribute_size += attribute.bytes;
}

void mesh_copy_attributes(Mesh* dest, Mesh* src) {
    free(dest->attributes);
    dest->attributes = malloc(sizeof(MeshAttribute) * src->attribute_count);

    // copy the attributes over
    memcpy(dest->attributes,
        src->attributes,
        sizeof(MeshAttribute) * src->attribute_count);

    dest->attribute_count = src->attribute_count;
    dest->attribute_size = src->attribute_size;
}

void mesh_dump_attributes(Mesh *mesh) {
    for (uint8_t i = 0; i < mesh->attribute_count; i++) {
        printf("ATTRIBUTE %d:\n", i);
        printf("Index: %p\n", mesh->attributes[i].index);
        printf("Size: %d\n", mesh->attributes[i].size);
        printf("Type: %d\n", (int)mesh->attributes[i].type);
    }
}

void mesh_free(Mesh *mesh) {
    free(mesh->vertices);
    free(mesh->attributes);
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    free(mesh);
}
