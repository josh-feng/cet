//
#include <string.h>

#include "lua.hpp"
#include "../core/cetcore.hpp"
#include "cetgsl.hpp"


////////////////////  CET COMPLEX/QUATERNION OPERATIONS  //////////////////////
static int Qadd ( lua_State *L ) {
  REAL q[] = {0, 0, 0, 0}; // or memset
  REAL *z;
  int sz = 0;
  if (lua_type(L, 1) == LUA_TNUMBER) q[0] = lua_tonumber(L, 1);
  else if (z = (REAL *) luaL_testudata(L, 1, CET_C)) memcpy(q, z, sz = SIZE_C);
  else if (z = (REAL *) luaL_testudata(L, 1, CET_H)) memcpy(q, z, sz = SIZE_H);
  else luaL_error(L, "arg #1 'number' expected");

  if (lua_type(L, 2) == LUA_TNUMBER) {
    q[0] += lua_tonumber(L, 2);
  }
  else if (z = (REAL *) luaL_testudata(L, 2, CET_C)) {
    q[0] += z[0];
    q[1] += z[1];
    if (sz < SIZE_C) sz = SIZE_C;
  }
  else if (z = (REAL *) luaL_testudata(L, 2, CET_H)) {
    q[0] += z[0];
    q[1] += z[1];
    q[2] += z[2];
    q[3] += z[3];
    if (sz < SIZE_H) sz = SIZE_H;
  }
  else {
    luaL_error(L, "arg #2 'number' expected");
  }

  z = (REAL *) lua_newuserdata(L, sz);
  luaL_setmetatable(L, sz == SIZE_C ? CET_C : CET_H);
  memcpy(z, q, sz);
  return 1;
}

static int Qsub ( lua_State *L ) {
  REAL q[] = {0, 0, 0, 0}; // or memset
  REAL *z;
  int sz = 0;
  if (lua_type(L, 1) == LUA_TNUMBER) q[0] = lua_tonumber(L, 1);
  else if (z = (REAL *) luaL_testudata(L, 1, CET_C)) memcpy(q, z, sz = SIZE_C);
  else if (z = (REAL *) luaL_testudata(L, 1, CET_H)) memcpy(q, z, sz = SIZE_H);
  else luaL_error(L, "arg #1 'number' expected");

  if (lua_type(L, 2) == LUA_TNUMBER) {
    q[0] -= lua_tonumber(L, 2);
  }
  else if (z = (REAL *) luaL_testudata(L, 2, CET_C)) {
    q[0] -= z[0];
    q[1] -= z[1];
    if (sz < SIZE_C) sz = SIZE_C;
  }
  else if (z = (REAL *) luaL_testudata(L, 2, CET_H)) {
    q[0] -= z[0];
    q[1] -= z[1];
    q[2] -= z[2];
    q[3] -= z[3];
    if (sz < SIZE_H) sz = SIZE_H;
  }
  else {
    luaL_error(L, "arg #2 'number' expected");
  }

  z = (REAL *) lua_newuserdata(L, sz);
  luaL_setmetatable(L, sz == SIZE_C ? CET_C : CET_H);
  memcpy(z, q, sz);
  return 1;
}

static int Qmul ( lua_State *L ) {
  REAL m, q[4];
  REAL *z1, *z2;
  int sz = 0;
  if (lua_type(L, 1) == LUA_TNUMBER) m = lua_tonumber(L, 1);
  else if (z1 = (REAL *) luaL_testudata(L, 1, CET_C)) sz = SIZE_C;
  else if (z1 = (REAL *) luaL_testudata(L, 1, CET_H)) sz = SIZE_H;
  else luaL_error(L, "arg #1 'number' expected");

  if (lua_type(L, 2) == LUA_TNUMBER) {
    m = lua_tonumber(L, 2);
    q[0] = z1[0] * m;
    q[1] = z1[1] * m;
    if (sz == SIZE_H) {
      q[2] = z1[2] * m;
      q[3] = z1[3] * m;
    }
  }
  else if (z2 = (REAL *) luaL_testudata(L, 2, CET_C)) {
    if (sz == SIZE_H) {
      q[0] = z1[0] * z2[0] - z1[1] * z2[1];
      q[1] = z1[1] * z2[0] + z1[0] * z2[1];
      q[2] = z1[2] * z2[0] + z1[3] * z2[1];
      q[3] = z1[3] * z2[0] - z1[2] * z2[1];
    }
    else if (sz) { // complex
      q[0] = z1[0] * z2[0] - z1[1] * z2[1];
      q[1] = z1[1] * z2[0] + z1[0] * z2[1];
    }
    else {
      q[0] = m * z2[0];
      q[1] = m * z2[1];
      sz = SIZE_C;
    }
  }
  else if (z2 = (REAL *) luaL_testudata(L, 2, CET_H)) {
    if (sz == SIZE_H) {
      q[0] = z1[0] * z2[0] - z1[1] * z2[1] - z1[2] * z2[2] - z1[3] * z2[3];
      q[1] = z1[0] * z2[1] + z1[1] * z2[0] + z1[2] * z2[3] - z1[3] * z2[2];
      q[2] = z1[0] * z2[2] - z1[1] * z2[3] + z1[2] * z2[0] + z1[3] * z2[1];
      q[3] = z1[0] * z2[3] + z1[1] * z2[2] - z1[2] * z2[1] + z1[3] * z2[0];
    }
    else {
      if (sz) {
        q[0] = z1[0] * z2[0] - z1[1] * z2[1];
        q[1] = z1[0] * z2[1] + z1[1] * z2[0];
        q[2] = z1[0] * z2[2] - z1[1] * z2[3];
        q[3] = z1[0] * z2[3] + z1[1] * z2[2];
      }
      else {
        q[0] = m * z2[0];
        q[1] = m * z2[1];
        q[2] = m * z2[2];
        q[3] = m * z2[3];
      }
      sz = SIZE_H;
    }
  }
  else {
    luaL_error(L, "arg #2 'number' expected");
  }

  z1 = (REAL *) lua_newuserdata(L, sz);
  luaL_setmetatable(L, sz == SIZE_C ? CET_C : CET_H);
  memcpy(z1, q, sz);
  return 1;
}

static int Qdiv ( lua_State *L ) { // H is a skew field
  REAL m, q[4];
  REAL *z1, *z2;
  int sz = 0;
  if (lua_type(L, 1) == LUA_TNUMBER) m = lua_tonumber(L, 1);
  else if (z1 = (REAL *) luaL_testudata(L, 1, CET_C)) sz = SIZE_C;
  else if (z1 = (REAL *) luaL_testudata(L, 1, CET_H)) sz = SIZE_H;
  else luaL_error(L, "arg #1 'number' expected");

  if (lua_type(L, 2) == LUA_TNUMBER) {
    m = lua_tonumber(L, 2);
    q[0] = z1[0] / m;
    q[1] = z1[1] / m;
    if (sz == SIZE_H) {
      q[2] = z1[2] / m;
      q[3] = z1[3] / m;
    }
  }
  else if (z2 = (REAL *) luaL_testudata(L, 2, CET_C)) {
    REAL x = z2[0], y = - z2[1];
    q[0] = x * x + y * y;
    x /= q[0];
    y /= q[0];
    if (sz == SIZE_H) {
      q[0] = z1[0] * x - z1[1] * y;
      q[1] = z1[1] * x + z1[0] * y;
      q[2] = z1[2] * x + z1[3] * y;
      q[3] = z1[3] * x - z1[2] * y;
    }
    else if (sz) { // complex
      q[0] = z1[0] * x - z1[1] * y;
      q[1] = z1[1] * x + z1[0] * y;
    }
    else {
      q[0] = m * x;
      q[1] = m * y;
      sz = SIZE_C;
    }
  }
  else if (z2 = (REAL *) luaL_testudata(L, 2, CET_H)) { // skew field
    REAL x = z2[0], y = - z2[1], z = - z2[2], w = - z2[3];
    q[0] = x * x + y + y + z * z + w * w;
    x /= q[0];
    y /= q[0];
    z /= q[0];
    w /= q[0];
    if (sz == SIZE_H) {
      q[0] = z1[0] * x - z1[1] * y - z1[2] * z - z1[3] * w;
      q[1] = z1[0] * y + z1[1] * x + z1[2] * w - z1[3] * z;
      q[2] = z1[0] * z - z1[1] * w + z1[2] * x + z1[3] * y;
      q[3] = z1[0] * w + z1[1] * z - z1[2] * y + z1[3] * x;
    }
    else {
      if (sz) {
        q[0] = z1[0] * x - z1[1] * y;
        q[1] = z1[0] * y + z1[1] * x;
        q[2] = z1[0] * z - z1[1] * w;
        q[3] = z1[0] * w + z1[1] * z;
      }
      else {
        q[0] = m * x;
        q[1] = m * y;
        q[2] = m * z;
        q[3] = m * w;
      }
      sz = SIZE_H;
    }
  }
  else {
    luaL_error(L, "arg #2 'number' expected");
  }

  z1 = (REAL *) lua_newuserdata(L, sz);
  luaL_setmetatable(L, sz == SIZE_C ? CET_C : CET_H);
  memcpy(z1, q, sz);
  return 1;
}

static int Qeq ( lua_State *L ) { // both should be userdata
  REAL *z1, *z2;
  int sz1, sz2;
  if      (z1 = (REAL *) luaL_testudata(L, 1, CET_C)) sz1 = SIZE_C;
  else if (z1 = (REAL *) luaL_testudata(L, 1, CET_H)) sz1 = SIZE_H;
  else luaL_error(L, "arg #1 'complex/quaternion' expected");
  if      (z2 = (REAL *) luaL_testudata(L, 2, CET_C)) sz2 = SIZE_C;
  else if (z2 = (REAL *) luaL_testudata(L, 2, CET_H)) sz2 = SIZE_H;
  else luaL_error(L, "arg #2 'complex/quaternion' expected");
  lua_pushboolean(L, z1[0] == z2[0] && z1[1] == z2[1] && (
      (sz1 > sz2 && z1[2] == 0 && z1[3] == 0) ||
      (sz1 < sz2 && z2[2] == 0 && z2[3] == 0) ||
      (sz1 == SIZE_H && z1[2] == z2[2] && z1[3] == z2[3])
    ) ? 1 : 0);
  return 1;
}

////////////////////////////  CET COMPLEX LIBRARY  ////////////////////////////
static int Cmod ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cpow ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cunm ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cidiv ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cband ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cbor ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cbxor ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cbnot ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cshl ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cshr ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cconcat ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Clen ( lua_State *L ) {
  REAL *z, *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  return 1;
}

static int Cindex ( lua_State *L ) {
  REAL *z = (REAL *) luaL_testudata(L, 1, CET_C);
  z[luaL_checkinteger(L, 2) % 2] = luaL_checknumber(L, 3);
  return 1;
}

static int Cnewindex ( lua_State *L ) {
  REAL *z = (REAL *) luaL_testudata(L, 1, CET_C);
  z[luaL_checkinteger(L, 2) % 2] = luaL_checknumber(L, 3);
  return 1;
}

static int Ccall ( lua_State *L ) { // fast copy
  REAL *z = (REAL *) luaL_testudata(L, 1, CET_C);
  REAL *w = (REAL *) lua_newuserdata(L, sizeof(REAL) * 2);
  luaL_setmetatable(L, CET_C);
  w[0] = z[0];
  w[1] = z[1];
  return 1;
}

static int Ctostring ( lua_State *L ) { // print
  REAL *z = (REAL *) luaL_testudata(L, 1, CET_C);
  lua_pushfstring(L, "(%f, %f)", z[0], z[1]);
  return 1;
}

extern const struct luaL_Reg cetCFunc[] = { // complex
  {"__add"     , Qadd     }, // addition +
  {"__sub"     , Qsub     }, // subtraction -
  {"__mul"     , Qmul     }, // multiplication *
  {"__div"     , Qdiv     }, // division /
  {"__eq"      , Qeq      }, // equal ==
  {"__mod"     , Cmod     }, // modulo %
  {"__pow"     , Cpow     }, // power ^
  {"__unm"     , Cunm     }, // negation -
  {"__idiv"    , Cidiv    }, // floor division //
  {"__band"    , Cband    }, // bitwise AND &
  {"__bor"     , Cbor     }, // bitwise OR |
  {"__bxor"    , Cbxor    }, // bitwise exclusive OR ~
  {"__bnot"    , Cbnot    }, // bitwise not ~
  {"__shl"     , Cshl     }, // bitwise shift left <<
  {"__shr"     , Cshr     }, // bitwise shift right >>
  {"__concat"  , Cconcat  }, // concatination ..
  {"__len"     , Clen     }, // length #
  // {"__lt"      , Clt      }, // less than < (not defined)
  // {"__le"      , Cle      }, // less equal <= (not defined)
  {"__index"   , Cindex   }, // indexing
  {"__newindex", Cnewindex}, // new index
  {"__call"    , Ccall    }, // func(args)
  {"__tostring", Ctostring}, // print
  //
  // {"__gc"   , Cgc   }, // garbage collection
  // {"__close", Cclose}, //
  // {"__mode" , Cmode }, //
  // {"__name" , Cname }, //
  {NULL, NULL}
};

////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
static int Htostring ( lua_State *L ) { // print
  REAL *z = (REAL *) luaL_testudata(L, 1, CET_H);
  lua_pushfstring(L, "(%f, %f, %f, %f)", z[0], z[1], z[2], z[3]);
  return 1;
}

extern const struct luaL_Reg cetHFunc[] = { // quaternion
  {"__add"     , Qadd     }, // addition +
  {"__sub"     , Qsub     }, // subtraction -
  {"__mul"     , Qmul     }, // multiplication *
  {"__div"     , Qdiv     }, // division /
  {"__eq"      , Qeq      }, // equal ==
  // {"__mod"     , Hmod     }, // modulo %
  // {"__pow"     , Hpow     }, // power ^
  // {"__unm"     , Hunm     }, // negation -
  // {"__idiv"    , Hidiv    }, // floor division //
  // {"__band"    , Hband    }, // bitwise AND &
  // {"__bor"     , Hbor     }, // bitwise OR |
  // {"__bxor"    , Hbxor    }, // bitwise exclusive OR ~
  // {"__bnot"    , Hbnot    }, // bitwise not ~
  // {"__shl"     , Hshl     }, // bitwise shift left <<
  // {"__shr"     , Hshr     }, // bitwise shift right >>
  // {"__concat"  , Hconcat  }, // concatination ..
  // {"__len"     , Hlen     }, // length #
  // {"__lt"      , Hlt      }, // less than < (not defined)
  // {"__le"      , Hle      }, // less equal <= (not defined)
  // {"__index"   , Hindex   }, // indexing
  // {"__newindex", Hnewindex}, // new index
  // {"__call"    , Hcall    }, // func(args)
  {"__tostring", Htostring}, // print
  //
  // {"__gc"   , Hgc   }, // garbage collection
  // {"__close", Hclose}, //
  // {"__mode" , Hmode }, //
  // {"__name" , Hname }, //
  {NULL, NULL}
};

////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
extern const struct luaL_Reg cetTFunc[] = { // tensor bundle
  {NULL, NULL}
};
// vim: ts=2 sw=2 sts=2 et foldenable fdm=marker fmr={{{,}}} fdl=1
