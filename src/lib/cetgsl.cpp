//
#include "lua.hpp"
#include "../core/cetcore.hpp"
#include "cetgsl.hpp"


////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
static int Cadd ( lua_State *L ) { // TODO
    lua_newuserdata(L, sizeof(cetData));
    luaL_setmetatable(L, "cet.T");
    return 1;
}

extern const struct luaL_Reg cetCFunc[] = { // complex
    {"__add"  , Cadd}, // addition
    // {"__sub"  , Csub}, // subtraction
    {NULL, NULL}
};

////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
extern const struct luaL_Reg cetHFunc[] = { // quaternion
    {NULL, NULL}
};

////////////////////////////  CET DATA STRUCTURE  /////////////////////////////
extern const struct luaL_Reg cetTFunc[] = { // tensor bundle
    {NULL, NULL}
};
