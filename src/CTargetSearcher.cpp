//
//  CTargetSearcher.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/6.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CTargetSearcher.hpp"
#include "CAbilityEntity.hpp"

CTargetSearcher::CTargetSearcher()
: center_(TARGET_CENTER_POINT)
, teams_(TARGET_TEAM_BOTH)
, types_(TARGET_TYPE_ALL)
, flags_(TARGET_FLAG_NONE)
{
}

CTargetSearcher::~CTargetSearcher() {
    
}

bool CTargetSearcher::IsHaveTargets(CAbilityEntity* caster) {
    return GetTargets(caster).size() > 0;
}

std::vector<CAbilityEntity*> CTargetSearcher::GetTargets(CAbilityEntity* caster) {
    return {};
}
