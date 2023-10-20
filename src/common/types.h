#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// header to declare types as intXX_t to ensure that they are the same size on
// all platforms

// signed integer types
typedef int8_t   i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// unsigned integer types
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// floating point types
typedef float f32;
typedef double f64;

#endif
