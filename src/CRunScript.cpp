//
//  CRunScprite.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/15.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CRunScript.hpp"
#include "CAbilityValue.hpp"

lua_State* CRunScript::L_ = 0;

CRunScript::CRunScript()
: scripteFile_("")
, function_("")
{
    if (!L_) {
        L_ = luaL_newstate();
        luaL_openlibs(L_);
    }
}

CRunScript::~CRunScript() {

}

void CRunScript::Execute() {
    std::string s = "require \"" + scripteFile_ + "\"";
    if (luaL_dostring(L_, s.c_str()) != LUA_OK) {
        const char *msg = lua_tostring(L_,-1);
        printf("ERROR--------------\n");
        printf("%s \n", msg);
        printf("ERROR--------------\n");
        return;
    }
    lua_getglobal(L_, function_.c_str());
    lua_newtable(L_);
    for (auto iter = params_.begin(); iter != params_.end(); ++iter) {
        lua_pushstring(L_, iter->first.c_str());
        if (iter->second->IsFloat()) {
            lua_pushnumber(L_, iter->second->GetValue<float>());
        }
        else if (iter->second->IsString()) {
            lua_pushstring(L_, iter->second->GetValue<std::string>().c_str());
        }
        lua_settable(L_, -3);
    }
    lua_call(L_, 1, 0);
}

void CRunScript::SetScript(std::string scriptFile, std::string function) {
    scripteFile_ = scriptFile;
    function_ = function;
}

void CRunScript::SetParam(std::string name, CAbilityValue* value) {
    params_[name] = value;
}
