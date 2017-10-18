//
//  CLuaStack.cpp
//  SkillLib
//
//  Created by yucong on 2017/10/18.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CLuaStack.hpp"

static CLuaStack* s_pInstance = NULL;

CLuaStack::CLuaStack() {
    
}

CLuaStack::~CLuaStack() {
    
}

CLuaStack* CLuaStack::getInstance() {
    if (!s_pInstance) {
        s_pInstance = new CLuaStack();
        s_pInstance->L_ = luaL_newstate();
        luaL_openlibs(s_pInstance->L_);
    }
    return s_pInstance;
}

CLuaStack* CLuaStack::BeginClass(std::string classname) {
    lua_newtable(L_);               /* stack: table */
    lua_setglobal(L_, classname.c_str());   /* _G[name] = table stack: */
    lua_getglobal(L_, classname.c_str());   /* stack: table */
    luaL_newmetatable(L_, classname.c_str());/* stack: table mt */
    lua_pushstring(L_, "__index");  /* stack: table mt str */
    lua_pushvalue(L_, -2);          /* stack: table mt str mt */
    lua_settable(L_, -3);           /* mt[str] = mt stack: table mt */
    lua_setmetatable(L_, -2);       /* setmetatable(table, mt) stack: table */
    lua_getmetatable(L_, -1);       /* stack: table mt */
    lua_insert(L_, -2);             /* stack: mt table */
    lua_pop(L_, 1);                 /* stack: mt */
    return this;
}

CLuaStack* CLuaStack::EndClass() {
    lua_pop(L_, 1);
    return this;
}

CLuaStack* CLuaStack::PushFunction(std::string name, lua_CFunction function) {
    lua_pushstring(L_, name.c_str()); /* stack: mt str */
    lua_pushcfunction(L_, function);  /* stack: mt str function */
    lua_settable(L_, -3);           /* mt[str] = function stack: mt */
    return this;
}


template<typename T>
CLuaStack* CLuaStack::PushCppFunction(std::string name, std::string classname, T memFunc){
    
    return this;
}

CLuaStack* CLuaStack::PushUserdata(void* data, std::string classname) {
    *(void**)lua_newuserdata(L_, sizeof(void*)) = data; /* stack: udname ud */
    if (classname != "") {
        luaL_getmetatable(L_, classname.c_str());       /* stack: udname ud classmt */
        lua_setmetatable(L_, -2);                       /* setmetatable(ud, classmt) stack: udname ud */
    }
    return this;
}

CLuaStack* CLuaStack::PushInteger(LUA_INTEGER value) {
    lua_pushinteger(L_, value);
    return this;
}

CLuaStack* CLuaStack::PushNumber(LUA_NUMBER value) {
    lua_pushnumber(L_, value);
    return this;
}

CLuaStack* CLuaStack::PushString(std::string value) {
    lua_pushstring(L_, value.c_str());
    return this;
}
