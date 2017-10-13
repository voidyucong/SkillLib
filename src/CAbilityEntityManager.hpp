//
//  CAbilityEntityManager.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/11.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbilityEntityManager_hpp
#define CAbilityEntityManager_hpp

#include <iostream>
#include <map>
#include <vector>
#include "CObject.hpp"

class CAbilityEntity;

class CAbilityEntityManager {
    typedef int TEAM_ID;
public:
    CAbilityEntityManager();
    ~CAbilityEntityManager();
    static CAbilityEntityManager* getInstance();
    void Clear();
    
    void AddTeam(TEAM_ID teamId, CAbilityEntity* entity);
    const std::vector<CAbilityEntity*>& GetTeam(TEAM_ID teamId);
    const std::vector<CAbilityEntity*>& GetOtherTeam(TEAM_ID teamId);
    void GetAllEntity(TARGET_LIST& list);
    
    uint GetEntityId(CAbilityEntity* entity);
    CAbilityEntity* GetEntityById(uint id);
private:
    std::map<TEAM_ID, std::vector<CAbilityEntity*>> entities_;
    std::map<uint, CAbilityEntity*> ids_;
};

#endif /* CAbilityEntityManager_hpp */
