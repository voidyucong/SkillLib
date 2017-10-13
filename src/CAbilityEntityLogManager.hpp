//
//  CAbilityEntityLogManager.hpp
//  SkillLib
//
//  Created by yucong on 2017/10/11.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbilityEntityLogManager_hpp
#define CAbilityEntityLogManager_hpp

#include <iostream>
#include <map>
#include <vector>

class CAbility;
class CAbilityEntity;

class CAbilityEntityLog {
public:
    CAbilityEntityLog():attacker_(0), victim_(0), ability_(0), value_(0) {}
    CAbilityEntityLog(uint attacker, uint victim, CAbility* ability, float value):attacker_(attacker), victim_(victim), ability_(ability), value_(value) {}
    ~CAbilityEntityLog() {}
    
private:
    uint attacker_;
    uint victim_;
    CAbility* ability_;
    float value_;
};

class CAbilityEntityLogManager {
public:
    CAbilityEntityLogManager();
    ~CAbilityEntityLogManager();
    static CAbilityEntityLogManager* getInstance();
    
    void AddFightLog(CAbilityEntity* attacker, CAbilityEntity* victim, float value, CAbility* ability);
    
private:
    std::map<uint, std::vector<CAbilityEntityLog*>> logs_;
};

#endif /* CAbilityEntityLog_hpp */
