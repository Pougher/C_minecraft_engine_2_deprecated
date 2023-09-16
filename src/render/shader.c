#include "shader.h"

Shader *shader_new(char *vs, char *fs) {
    Shader *new_shader = malloc(sizeof(Shader));
    new_shader->id = 0;

    const char* vshader_code = read_file(vs);
    const char* fshader_code = read_file(fs);
    if (vshader_code == NULL || fshader_code == NULL) {
        log_error("Cannot generate shader - files missing");
        return new_shader;
    }

    unsigned int vertex;
    unsigned int fragment;
    int success;
    char info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vshader_code, NULL);
    glCompileShader(vertex);

    // check if there are any errors, and if there are, print them
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info);
        log_error(info);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fshader_code, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info);
        log_error(info);
    }
    // now link the two shaders and generate a program
    new_shader->id = glCreateProgram();
    glAttachShader(new_shader->id, vertex);
    glAttachShader(new_shader->id, fragment);
    glLinkProgram(new_shader->id);

    // output any linking errors
    glGetProgramiv(new_shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(new_shader->id, 512, NULL, info);
        log_error(info);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free((char*)vshader_code);
    free((char*)fshader_code);
#ifndef NO_LOGS
    char shader_log_msg[strlen(fs) + strlen(vs) + 128];
    sprintf(
        shader_log_msg,
        "Generated shader %d from '%s' and '%s'",
        new_shader->id,
        vs,
        fs);
    log_info(shader_log_msg);
#endif
    return new_shader;
}

void shader_load(Shader *shader, char *vs, char *fs) {
    shader->id = 0;

    const char* vshader_code = read_file(vs);
    const char* fshader_code = read_file(fs);
    if (vshader_code == NULL || fshader_code == NULL) {
        log_error("Cannot generate shader - files missing");
        return;
    }

    unsigned int vertex;
    unsigned int fragment;
    int success;
    char info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vshader_code, NULL);
    glCompileShader(vertex);

    // check if there are any errors, and if there are, print them
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info);
        log_error(info);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fshader_code, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info);
        log_error(info);
    }
    // now link the two shaders and generate a program
    shader->id = glCreateProgram();
    glAttachShader(shader->id, vertex);
    glAttachShader(shader->id, fragment);
    glLinkProgram(shader->id);

    // output any linking errors
    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->id, 512, NULL, info);
        log_error(info);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free((char*)vshader_code);
    free((char*)fshader_code);
#ifndef NO_LOGS
    char shader_log_msg[strlen(fs) + strlen(vs) + 128];
    sprintf(
        shader_log_msg,
        "Generated shader %d from '%s' and '%s'",
        shader->id,
        vs,
        fs);
    log_info(shader_log_msg);
#endif
}

void shader_use(Shader *shader) {
    glUseProgram(shader->id);
}

void shader_free(Shader *shader) {
    glDeleteProgram(shader->id);
    free(shader);
}

void shader_delete(Shader *shader) {
    glDeleteProgram(shader->id);
}

void shader_setbool(Shader *shader, const char *name, bool val) {
    glUniform1i(GL_UNIFORM_LOCATION, val);
}

void shader_setint(Shader *shader, const char *name, int val) {
    glUniform1i(GL_UNIFORM_LOCATION, val);
}

void shader_setfloat(Shader *shader, const char *name, float val) {
    glUniform1f(GL_UNIFORM_LOCATION, val);
}

void shader_setvec3(Shader *shader, const char *name, vec3 val) {
    glUniform3fv(GL_UNIFORM_LOCATION, 1, &val[0]);
}

void shader_setmat4(Shader *shader, const char *name, mat4 val) {
    glUniformMatrix4fv(GL_UNIFORM_LOCATION, 1, GL_FALSE, &val[0][0]);
}
