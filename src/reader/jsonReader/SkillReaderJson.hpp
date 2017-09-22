//
//  SkillReaderJson.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/12.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef SkillReaderJson_hpp
#define SkillReaderJson_hpp

#include <stdio.h>
#include <map>
#include "rapidjson.h"
#include "document.h"

class CAbility;
class CAbilityValue;
class CEvent;
class CModifierEvent;
class COperate;
class CModifierData;

class SkillReaderJson {
public:
    SkillReaderJson();
    ~SkillReaderJson();
    static SkillReaderJson* getInstance();
    
    CAbility* AbilityFromFile(std::string fileName);
    CAbility* CreateAbility(const rapidjson::Value& json);
    
    void ParseSpecialValue(const rapidjson::Value& json, CAbility* ability);
    CAbilityValue* CreateVariableList(const rapidjson::Value& item, std::string type, CAbility* ability);
    
    void ParseAbilityEvent(const rapidjson::Value& json, CAbility* ability);
    CEvent* CreateAbilityEvent(const rapidjson::Value& json, std::string eventName, CAbility* ability);
    
    void ParseModifierEvent(const rapidjson::Value& json, CModifierData* modifier, CAbility* ability);
    CModifierEvent* CreateModifierEvnt(const rapidjson::Value& json, std::string eventName, CAbility* ability);
    
    void ParseOperate(const rapidjson::Value& json, CEvent* event, CAbility* ability);
    void ParseOperateTarget(const rapidjson::Value& json, COperate* operate, CAbility* ability);
    
    void ParseModifiers(const rapidjson::Value& json, CAbility* ability);
    CModifierData* CreateModifier(const rapidjson::Value& json, std::string name, CAbility* ability);
private:
    
};

#endif /* SkillReaderJson_hpp */
