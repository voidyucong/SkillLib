//
//  CRunScript.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/15.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CRunScript_hpp
#define CRunScript_hpp

#include <iostream>
#include <map>
#include "CObject.hpp"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CAbilityValue;
class CAbility;
class CAbilityEntity;

class CRunScript : public CObject {
public:
    CRunScript();
    ~CRunScript();
    
    void Execute();
    void SetLuaState(lua_State* L) { L_ = L; }
    void SetScript(std::string scriptFile, std::string function);
    void SetParam(std::string name, CAbilityValue* value);
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    void SetTarget(CAbilityEntity* target) { target_ = target; }
    void SetAbility(CAbility* ability) { ability_ = ability; }
    
    std::string GetScript() { return scripteFile_; }
private:
    std::string scripteFile_;
    std::string function_;
    std::map<std::string, CAbilityValue*> params_;
    CAbilityEntity* caster_;
    CAbilityEntity* target_;
    CAbility* ability_;
    
    static lua_State* L_;
};

#endif /* CRunScprite_hpp */
