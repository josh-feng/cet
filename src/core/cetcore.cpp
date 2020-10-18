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

// lua
#include "lua.hpp"

// cetcore
#include "cetcore.hpp"

// num lib: GSL
#include "../lib/cetgsl.hpp"

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

///////////////////////////////////////////////////////////////////////////////
// z = cetcore.qtrn(0, 1) -- complex
// h = cetcore.qtrn(0, 1, 0, 0) -- quaternion
// c = cetcore.colvec() -- vector (column vector)
// r = cetcore.rowvec() -- vector (row vector)
// m = cetcore.matrix() -- matrix -- b = cet.spm() -- sparse matrix
// t = cetcore.tensor() -- tensor
//
// pde {"pde", pdeCreator}, // pde system object

static int cQtrn ( lua_State *L ) {
    // quaternion/space-time math: metric (-1, 1, 1, 1)
    if (lua_gettop(L) < 3) { // <= 2 args: complex
        REAL *z = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
        z[0] = luaL_checknumber(L, 1);
        z[1] = luaL_checknumber(L, 2);
        luaL_getmetatable(L, "cet.C");
    } else { // >= 3 args: quaternion
        REAL *q = (REAL *) lua_newuserdata(L, sizeof(REAL) * 4);
        q[0] = luaL_checknumber(L, 1);
        q[1] = luaL_checknumber(L, 2);
        q[2] = luaL_checknumber(L, 3);
        q[3] = luaL_checknumber(L, 4);
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
    {"qtrn"  , cQtrn  }, // complex/(1, 0) quaternion/(1, 0, 0, 0)
    {"colvec", cColvec}, // vector (column vector)
    {"rowvec", cRowvec}, // vector (row vector)
    {"matrix", cMatrix}, // matrix -- b = cet.spm() -- sparse matrix
    {"domain", cDomain}, // cw complex space
    {"tensor", cTensor}, // tensor field on domain
    {NULL, NULL}
};

LUA_API int luaopen_cetcore ( lua_State *L ) { // require('cetcore')
    // complex type
    luaL_newmetatable(L, "cet.C");
    luaL_setfuncs(L, cetCFunc, 0);
    // quaternion type
    luaL_newmetatable(L, "cet.H");
    luaL_setfuncs(L, cetHFunc, 0);
    // bundle type
    luaL_newmetatable(L, "cet.T");
    luaL_setfuncs(L, cetTFunc, 0);

    // cet object creator
    luaL_newlib(L, cetCoreFunc);
    return 1;
}

// vim: ts=4 sw=4 sts=4 et foldenable fdm=marker fmr={{{,}}} fdl=1
