//
//  CLuaStack.hpp
//  SkillLib
//
//  Created by yucong on 2017/10/18.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CLuaStack_hpp
#define CLuaStack_hpp

#include <iostream>
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CLuaStack {
public:
    CLuaStack();
    ~CLuaStack();
    static CLuaStack* getInstance();
    lua_State* GetState() { return L_; }
    
    CLuaStack* BeginClass(std::string classname);
    CLuaStack* EndClass();
    
    CLuaStack* PushFunction(std::string name, lua_CFunction function);
    template<typename T>
    CLuaStack* PushCppFunction(std::string name, std::string classname, T memFunc);
    CLuaStack* PushUserdata(void* data, std::string classname = "");
    CLuaStack* PushInteger(LUA_INTEGER value);
    CLuaStack* PushNumber(LUA_NUMBER value);
    CLuaStack* PushString(std::string value);
private:
    lua_State* L_;
};



#endif /* CLuaStack_hpp */
