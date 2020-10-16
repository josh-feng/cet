//
// Good API for data interchange
// We don't want to re-invant the wheel
// numerical data:
//  complex number
//  vector
//  map
//  abstract object
// audio:
// video:
//  image: png, jpg, svg
//  film: avi, mp4
// network:
//  socket:
// -------------------------------------------------------------------------
//
// equation: ODE/PDE --> Algebraic
// ode: V(idx = range) ->
//  ode = cet:ode()
//
// pde: V(idx = range) -> CW-complex decomp domain
//  pde = cet:pde()
//      pde:domain() -- indep var and range
//      pde:var()    -- dep var
//      pde:bc()
//      pde:eq()
//      pde:solve()
//  example:
//      pde:atlas()
//      pde:patch()
//      pde:domain() -- indep var and range (mesh) manifold
//      pde:bndry()
//      pde:var()    -- dep var (field)
//      pde:bc()
//      pde:eq()
//      pde:solve()
//
//

// lua
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// cetcore
#include "cetcore.hpp"

// -------------------------------------------------------------------------
// domain/topology: simplicial complex
//  simplicial comlex
//  delta comlex
//  cw complex
//
// equation: ODE/PDE --> Algebraic
// ode: V(idx = range) ->
//  ode = cet:ode()
//
// pde: V(idx = range) ->
//  pde = cet:pde()
//      pde:domain() -- indep var and range
//      pde:var()    -- dep var
//      pde:bc(v() + v() == c() + 2)
//      pde:eq()
//      pde:solve()
//  example:
//      pde:atlas()
//      pde:patch()
//      pde:domain() -- indep var and range (mesh) manifold
//      pde:bndry()
//      pde:var()    -- dep var (field)
//      pde:bc()
//      pde:eq()
//      pde:solve()
//
//

static int myfunc ( lua_State *L ) {
    return 1;
}

// meta function
static const struct luaL_Reg cetcore_m[] = {
    {"__newindex", myfunc},
    {NULL, NULL}
};

///////////////////////////////////////////////////////////////////////////////
// z = cet.qtn(0, 1) -- complex
// q = cet.qtn(0, 1, 0, 0) -- quaternion
// c = cet.vec() -- vector (column vector)
// r = cet.row() -- vector (row vector)
// m = cet.mat() -- matrix -- b = cet.spm() -- sparse matrix
// m = cet.domain() -- cw complex space
// a = cet.tensor() -- tensor (manifold)
//
// pde {"pde", pdeCreator}, // pde system object

static int cQtrn ( lua_State *L ) {
    // quaternion/space-time math: metric (-1, 1, 1, 1)
    // <= 2 args: complex
    // >= 3 args: quaternion
    return 1;
}

static int cColvec ( lua_State *L ) {
    return 1;
}

static int cRowvec ( lua_State *L ) {
    return 1;
}

static int cMatrix ( lua_State *L ) {
    return 1;
}

static int cDomain ( lua_State *L ) {
    return 1;
}

static int cTensor ( lua_State *L ) {
    return 1;
}

//
static const struct luaL_Reg cetCoreFunc[] = {
    {"qtrn"  , cQtrn  }, // complex/(1, 0) quaternion/(1, 0, 0, 0)
    {"colvec", cColvec}, // vector (column vector)
    {"rowvec", cRowvec}, // vector (row vector)
    {"matrix", cMatrix}, // matrix -- b = cet.spm() -- sparse matrix
    {"domain", cDomain}, // cw complex space
    {"tensor", cTensor}, // tensor field on domain
    {NULL, NULL}
};

LUA_API int luaopen_cetcore ( lua_State *L ) { // require('cetcore')
    luaL_newlib(L, cetCoreFunc);
    return 1;
}

// vim: ts=4 sw=4 sts=4 et foldenable fdm=marker fmr={{{,}}} fdl=1
