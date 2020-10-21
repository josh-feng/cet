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
//      pde:bc() -- same as eq (dominant/enforce)
//      pde:eq() -- discretization
//          pde:eq(domain1, f1(V(index)) == g1(V(index)))
//          pde:eq(domain2, f2(V(index)) == g2(V(index)))
//      pde:solve()
//      pde:assign(domain1, ) -- TODO
//
//

#include "lua.hpp"              // lua
#include "cetcore.hpp"          // cetcore
#include "../lib/cetgsl.hpp"    // num implementation: GSL

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
//    pde:domain() -- indep var and range
//    pde:var()    -- dep var
//    pde:bc(v() + v() == c() + 2)
//    pde:eq()
//    pde:solve()
//  example:
//    pde:atlas()
//    pde:patch()
//    pde:domain() -- indep var and range (mesh) manifold
//    pde:bndry()
//    pde:var()    -- dep var (field)
//    pde:bc()
//    pde:eq()
//    pde:solve()
//

const char *CET_C = "cet.C";
const char *CET_H = "cet.H";
const char *CET_T = "cet.T";

///////////////////////////////////////////////////////////////////////////////
// z = cetcore.cq(0, 1) -- complex
// h = cetcore.cq(0, 1, 0, 0) -- quaternion
// c = cetcore.colvec() -- vector (column vector)
// r = cetcore.rowvec() -- vector (row vector)
// m = cetcore.matrix() -- matrix -- b = cet.spm() -- sparse matrix
// t = cetcore.tensor() -- tensor
//
// pde {"pde", pdeCreator}, // pde system object

static int cCq ( lua_State *L ) { // Complex or Quaterion
  if (lua_gettop(L) < 3) { // <= 2 args: complex
    REAL *z = (REAL *) lua_newuserdata(L, SIZE_C);
    z[0] = lua_tonumber(L, 1); // default 0
    z[1] = lua_tonumber(L, 2); // default 0
    luaL_getmetatable(L, "cet.C");
  }
  else { // >= 3 args: quaternion space-time metric (-1, 1, 1, 1)
    REAL *q = (REAL *) lua_newuserdata(L, SIZE_H);
    q[0] = luaL_checknumber(L, 1);
    q[1] = luaL_checknumber(L, 2);
    q[2] = luaL_checknumber(L, 3);
    q[3] = lua_tonumber(L, 4); // default 0
    luaL_getmetatable(L, "cet.H");
  }
  lua_setmetatable(L, -2);
  return 1;
}

static int cColvec ( lua_State *L ) {
  lua_newuserdata(L, sizeof(cetData));
  luaL_setmetatable(L, "cet.T");
  return 1;
}

static int cRowvec ( lua_State *L ) {
  lua_newuserdata(L, sizeof(cetData));
  luaL_setmetatable(L, "cet.T");
  return 1;
}

static int cMatrix ( lua_State *L ) {
  lua_newuserdata(L, sizeof(cetData));
  luaL_setmetatable(L, "cet.T");
  return 1;
}

static int cDomain ( lua_State *L ) {
  lua_newuserdata(L, sizeof(cetData));
  luaL_setmetatable(L, "cet.T");
  return 1;
}

static int cTensor ( lua_State *L ) {
  lua_newuserdata(L, sizeof(cetData));
  luaL_setmetatable(L, "cet.T");
  return 1;
}

//
static const struct luaL_Reg cetCoreFunc[] = {
  {"cq"    , cCq    }, // complex/(1, 0) quaternion/(1, 0, 0, 0)
  {"colvec", cColvec}, // vector (column vector)
  {"rowvec", cRowvec}, // vector (row vector)
  {"matrix", cMatrix}, // matrix -- b = cet.spm() -- sparse matrix
  {"domain", cDomain}, // cw complex space
  {"tensor", cTensor}, // tensor field on domain
  {NULL, NULL}
};

LUA_API int luaopen_cetcore ( lua_State *L ) { // require('cetcore')
  // quaternion type
  luaL_newmetatable(L, CET_H);
  luaL_setfuncs(L, cetHFunc, 0);
  // bundle type
  luaL_newmetatable(L, CET_T);
  luaL_setfuncs(L, cetTFunc, 0);
  // complex type
  luaL_newmetatable(L, CET_C);
  luaL_setfuncs(L, cetCFunc, 0);

  // cet object creator
  luaL_newlib(L, cetCoreFunc);
  return 1;
}
// vim: ts=2 sw=2 sts=2 et foldenable fdm=marker fmr={{{,}}} fdl=1
