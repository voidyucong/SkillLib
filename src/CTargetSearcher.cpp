//
//  CTargetSearcher.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/6.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CTargetSearcher.hpp"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CAbilityEntityManager.hpp"
#include "CAbilityValue.hpp"

CTargetSearcher::CTargetSearcher()
: center_(TARGET_CENTER_CASTER)
, teams_(TARGET_TEAM_BOTH)
, types_(TARGET_TYPE_ALL)
, flags_(TARGET_FLAG_NONE)
, radius_(0)
{
}

CTargetSearcher::~CTargetSearcher() {
    targets_.clear();
}

bool CTargetSearcher::IsHaveTargets(CAbilityEntity* caster, CAbility* ability) {
    return GetTargets(caster, ability).size() > 0;
}

std::vector<CAbilityEntity*> CTargetSearcher::GetTargets(CAbilityEntity* caster, CAbility* ability) {
    if (teams_ == TARGET_TEAM_NONE) return {};
    std::vector<CAbilityEntity*> team;
    
    // radius
    if (radius_) {  // 群体
        float radius = 0.f;
        if (radius_->IsArray()) {
            radius = radius_->GetArrayValueByIndex(ability->GetLevel())->GetValue<float>();
        }
        else {
            radius = radius_->GetValue<float>();
        }
        
        // team
        switch (teams_) {
            case TARGET_TEAM_BOTH:
                team = CAbilityEntityManager::getInstance()->GetAllEntity();
                break;
            case TARGET_TEAM_FRIENDLY:
                team = CAbilityEntityManager::getInstance()->GetTeam(caster->GetTeamId());
                break;
            case TARGET_TEAM_ENEMY:
                team = CAbilityEntityManager::getInstance()->GetOtherTeam(caster->GetTeamId());
                break;
            default:
                break;
        }
    }
    else {  // 单体
        // center
        switch (center_) {
            case TARGET_CENTER_CASTER:
                team.push_back(caster);
                break;
            case TARGET_CENTER_TARGET:
                break;
            case TARGET_CENTER_POINT:
                break;
            case TARGET_CENTER_ATTACKER:
                break;
            case TARGET_CENTER_PROJECTILE:
                break;
            default:
                break;
        }
    }
    
    // type
    if (types_ != TARGET_TYPE_ALL && types_ != TARGET_TYPE_NONE) {
        for (auto iter = team.begin(); iter != team.end();) {
            if ((int)types_ != (int)(*iter)->GetType())
                team.erase(iter);
            else
                ++iter;
        }
    }
    // flag
    if (flags_ != TARGET_FLAG_NONE) {
        
    }
    
    return team;
}
