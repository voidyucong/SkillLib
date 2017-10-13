//
//  CAbilityEntityManager.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/11.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbilityEntityManager.hpp"
#include "CAbilityEntity.hpp"

static CAbilityEntityManager* s_pInstance = NULL;

CAbilityEntityManager::CAbilityEntityManager() {
    
}

CAbilityEntityManager::~CAbilityEntityManager() {
    
}

CAbilityEntityManager* CAbilityEntityManager::getInstance() {
    if (!s_pInstance) {
        s_pInstance = new CAbilityEntityManager();
    }
    return s_pInstance;
}

void CAbilityEntityManager::Clear() {
    for (auto iter = entities_.begin(); iter != entities_.end(); ++iter) {
        iter->second.clear();
    }
    entities_.clear();
}

void CAbilityEntityManager::AddTeam(TEAM_ID teamId, CAbilityEntity* entity) {
    if (entities_.find(teamId) == entities_.end())
        entities_[teamId] = {};
    auto& entities = entities_[teamId];
    entities.push_back(entity);
    entity->SetTeamId(teamId);
}

const std::vector<CAbilityEntity*>& CAbilityEntityManager::GetTeam(TEAM_ID teamId) {
    return entities_[teamId];
}

const std::vector<CAbilityEntity*>& CAbilityEntityManager::GetOtherTeam(TEAM_ID teamId) {
    for (auto iter = entities_.begin(); iter != entities_.end(); ++iter) {
        if (iter->first != teamId) {
            return iter->second;
        }
    }
    return {};
}

void CAbilityEntityManager::GetAllEntity(TARGET_LIST& list) {
    for (auto iter = entities_.begin(); iter != entities_.end(); ++iter) {
        for (auto entity : iter->second) {
            list.push_back(entity);
        }
    }
}

static uint s_id = 1;
uint CAbilityEntityManager::GetEntityId(CAbilityEntity* entity) {
    for (auto iter = ids_.begin(); iter != ids_.end(); ++iter) {
        if (entity == iter->second) return iter->first;
    }
    ids_[s_id] = entity;
    return s_id++;
}

CAbilityEntity* CAbilityEntityManager::GetEntityById(uint id) {
    return ids_[id];
}
