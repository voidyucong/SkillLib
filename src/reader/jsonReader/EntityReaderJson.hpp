//
//  EntityReaderJson.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef EntityReaderJson_hpp
#define EntityReaderJson_hpp

#include <iostream>
#include "ReaderJsonUtil.h"
class CAbility;
class CabilityEntity;

class EntityReaderJson {
public:
    EntityReaderJson();
    ~EntityReaderJson();
    static EntityReaderJson* getInstance();
    
    CAbilityEntity* EntityFromFile(std::string fileName);
    
    CAbilityEntity* CreateEntity(const rapidjson::Value& json);
};

#endif /* EntityReaderJson_hpp */
