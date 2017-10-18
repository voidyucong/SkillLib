//
//  CRunScprite.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/15.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CRunScript.hpp"
#include "CAbilityValue.hpp"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"

lua_State* CRunScript::L_ = 0;

static int CAbility_GetName(lua_State* L) {
    CAbility* instance = *((CAbility**)lua_touserdata(L, -1));
    lua_pushstring(L, instance->GetName().c_str());
    return 1;
}
static int CAbilityEntity_GetCurHp(lua_State* L) {
    CAbilityEntity* instance = *((CAbilityEntity**)lua_touserdata(L, -1));
    lua_pushnumber(L, instance->GetCurHp());
    return 1;
}

CRunScript::CRunScript()
: scripteFile_("")
, function_("")
{
    if (!L_) {
        L_ = CLuaStack::getInstance()->GetState();
        
        // test
        CLuaStack::getInstance()
            ->BeginClass("CAbility")
                ->PushFunction("GetName", &CAbility_GetName)
            ->EndClass();
        CLuaStack::getInstance()
            ->BeginClass("CAbilityEntity")
                ->PushFunction("GetCurHp", &CAbilityEntity_GetCurHp)
            ->EndClass();
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
        if (iter->second->IsFloat()) {
            CLuaStack::getInstance()->PushString(iter->first)->PushNumber(iter->second->GetValue<float>());
        }
        else if (iter->second->IsString()) {
            CLuaStack::getInstance()->PushString(iter->first)->PushString(iter->second->GetValue<std::string>());
        }
        lua_settable(L_, -3);
    }
    CLuaStack::getInstance()->PushString("ability")->PushUserdata(ability_, "CAbility");
    lua_settable(L_, -3);                       /* table[str] = userdata stack: function table */
    CLuaStack::getInstance()->PushString("caster")->PushUserdata(caster_, "CAbilityEntity");
    lua_settable(L_, -3);                       /* table[str] = userdata stack: function table */
    CLuaStack::getInstance()->PushString("target")->PushUserdata(target_, "CAbilityEntity");
    lua_settable(L_, -3);                       /* table[str] = userdata stack: function table */
    lua_call(L_, 1, 0);
}

void CRunScript::SetScript(std::string scriptFile, std::string function) {
    scripteFile_ = scriptFile;
    function_ = function;
}

void CRunScript::SetParam(std::string name, CAbilityValue* value) {
    params_[name] = value;
}
