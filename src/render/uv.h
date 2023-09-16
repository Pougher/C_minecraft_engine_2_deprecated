#ifndef UV_H
#define UV_H

#include <stdint.h>

// structure for defining uv values (integer)
typedef struct {
    int32_t u;
    int32_t v;
} TexUVi;

// structure for defining uv values (floats)
typedef struct {
    float u;
    float v;
} TexUV;

#endif
