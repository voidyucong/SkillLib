//
//  CAbilityEntityLogManager.cpp
//  SkillLib
//
//  Created by yucong on 2017/10/11.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbilityEntityLogManager.hpp"
#include "CAbilityEntityManager.hpp"

static CAbilityEntityLogManager* s_pInstance = NULL;

CAbilityEntityLogManager::CAbilityEntityLogManager() {
    
}

CAbilityEntityLogManager::~CAbilityEntityLogManager() {
    for (auto iter = logs_.begin(); iter != logs_.end(); ++iter) {
        for (auto log : iter->second) {
            if (log) {
                delete log;
                log = 0;
            }
        }
    }
}

CAbilityEntityLogManager* CAbilityEntityLogManager::getInstance() {
    if (!s_pInstance) s_pInstance = new CAbilityEntityLogManager();
    return s_pInstance;
}

void CAbilityEntityLogManager::AddFightLog(CAbilityEntity* attacker, CAbilityEntity* victim, float value, CAbility* ability) {
    uint attackerId = CAbilityEntityManager::getInstance()->GetEntityId(attacker);
    uint victimId = CAbilityEntityManager::getInstance()->GetEntityId(victim);
    CAbilityEntityLog* log = new CAbilityEntityLog(attackerId, victimId, ability, value);
    if (logs_.find(attackerId) == logs_.end()) logs_[attackerId] = {};
    if (logs_.find(victimId) == logs_.end()) logs_[victimId] = {};
    logs_[attackerId].push_back(log);
    logs_[victimId].push_back(log);
}
