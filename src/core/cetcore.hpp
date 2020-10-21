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

// struct { REAL z[2]; } cetComplex; // quaternion/complex
// struct { REAL q[4]; } cetQuaternion; // quaternion/complex

#define SIZE_C  (sizeof(REAL) * 2)
#define SIZE_H  (sizeof(REAL) * 4)

////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
// z = cetcore.qtrn(0, 1) -- complex
// h = cetcore.qtrn(0, 1, 0, 0) -- quaternion
// c = cetcore.colvec() -- vector (column vector)
// r = cetcore.rowvec() -- vector (row vector)
// m = cetcore.matrix() -- matrix -- b = cet.spm() -- sparse matrix
// t = cetcore.tensor() -- tensor

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
  BYTE bndl; // 1-15:dimensionss 0:reserved
  void *ptr; // dimension array + data array (quaternion/complex)
} cetData;

extern const char *CET_C;
extern const char *CET_H;
extern const char *CET_T;

extern const struct luaL_Reg cetCFunc[]; // complex
extern const struct luaL_Reg cetHFunc[]; // quaternion
extern const struct luaL_Reg cetTFunc[]; // tensor bundle

//
LUA_API int luaopen_cetcore (lua_State *);

#endif
// vim: ts=2 sw=2 sts=2 et foldenable fdm=marker fmr={{{,}}} fdl=1
