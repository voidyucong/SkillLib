//
//  SkillReaderJson.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/12.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef SkillReaderJson_hpp
#define SkillReaderJson_hpp

#include <iostream>
#include <map>
#include "ReaderJsonUtil.h"

class CAbility;
class CAbilityValue;
class CEvent;
class CModifierEvent;
class COperate;
class CModifierData;
class CTargetSearchType;

class SkillReaderJson {
public:
    SkillReaderJson();
    ~SkillReaderJson();
    static SkillReaderJson* getInstance();
    
    CAbility* AbilityFromFile(std::string fileName);
    CAbility* CreateAbility(const rapidjson::Value& json);
    
    void ParseSpecialValue(const rapidjson::Value& json, CAbility* ability);
    
    void ParseAbilityEvent(const rapidjson::Value& json, CAbility* ability);
    CEvent* CreateAbilityEvent(const rapidjson::Value& json, std::string eventName, CAbility* ability);
    
    void ParseModifierEvent(const rapidjson::Value& json, CModifierData* modifier, CAbility* ability);
    CModifierEvent* CreateModifierEvnt(const rapidjson::Value& json, std::string eventName, CAbility* ability);
    
    void ParseOperate(const rapidjson::Value& json, CEvent* event, CAbility* ability);
    CTargetSearchType* ParseTarget(const rapidjson::Value& json, CAbility* ability);
    
    void ParseModifiers(const rapidjson::Value& json, CAbility* ability);
    CModifierData* CreateModifier(const rapidjson::Value& json, std::string name, CAbility* ability);
    
    long GetDamageType(const rapidjson::Value& item, CAbility* ability, long def = 0);
};

#endif /* SkillReaderJson_hpp */
