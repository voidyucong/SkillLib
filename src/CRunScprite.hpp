//
//  CRunScprite.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/15.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CRunScprite_hpp
#define CRunScprite_hpp

#include <iostream>
#include <map>
#include "CObject.hpp"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CRunScprite : public CObject {
public:
    CRunScprite();
    ~CRunScprite();
    
    void Execute();
    void SetLuaState(lua_State* L) { L_ = L; }
    void SetScript(std::string scriptFile, std::string function);
    void SetParam(std::string name, CObject* value);
    
    std::string GetScript() { return scripteFile_; }
private:
    std::string scripteFile_;
    std::string function_;
    std::map<std::string, CObject*> params_;
    
    static lua_State* L_;
};

#endif /* CRunScprite_hpp */
