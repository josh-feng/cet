// API for data interchange (We don't want to re-invant the wheel)
#ifndef _cetcore_hpp
#define _cetcore_hpp

/////////////////////////////////  GENERAL  ////////////////////////////////////
#include <stdint.h>

typedef uint8_t BYTE;     // BYTE = unsigned 8 bit value
typedef uint16_t WORD;    // WORD = unsigned 16 bit value
typedef uint32_t DWORD;   // DWORD = unsigned 32 bit value

typedef unsigned int UINT;
typedef double REAL;

typedef REAL COMPLEX[2];
typedef REAL QUATERNION[4];

/////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
// numerical data:
//  complex number
//  vector
//  map
//  abstract object

// z = cet.qtn(0, 1) -- complex
// q = cet.qtn(0, 1, 0, 0) -- quaternion
// c = cet.vec() -- vector (column vector)
// r = cet.row() -- vector (row vector)
// m = cet.mat() -- matrix -- b = cet.spm() -- sparse matrix
// a = cet.tsr() -- tensor

#define MASKBNDL 0xF0 // bundle
#define MASKDIMS 0x0F // dimensions

// value type (bundle)
#define TINT  0x00 // integer
#define TREAL 0x10 // real
#define TCOMP 0x20 // complex
#define TQUAT 0x30 // quaternion
// flag
#define TSPAR 0x40 // sparse
#define TZIP  0x80 // compressed

// userdata: position/numerical index

struct { // bundle
    BYTE bndl; // 0-15 / dims (WORD?)
    void *ptr; // dimension array + data array (quaternion/complex)
} cetdata;


//

LUA_API int luaopen_cetcore (lua_State *);

#endif
// vim: ts=4 sw=4 sts=4 et foldenable fdm=marker fmr={{{,}}} fdl=1
