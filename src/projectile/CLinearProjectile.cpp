//
//  CLinearProjectile.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CLinearProjectile.hpp"
#include "CScheduleManager.h"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CAbilityValue.hpp"
#include "TimeUtil.h"
#include "CTargetSearcher.hpp"

CLinearProjectile::CLinearProjectile()
: CLinearProjectile(0)
{}

CLinearProjectile::CLinearProjectile(CLinearProjectileData* data)
: data_(data)
, castTimestamp_(SKB::TimeUtil::GetSeconds())
{
}

CLinearProjectile::~CLinearProjectile()
{
    CScheduleManager::getInstance()->RemoveSchedule(this);
    hitTargets_.clear();
}

void CLinearProjectile::Update(float dt) {
    CAbility* ability = data_->GetAbility();
    int level = ability->GetLevel();
    double passTime = SKB::TimeUtil::GetSeconds() - castTimestamp_;
    CVector currentPosition = data_->GetCastPosition() + data_->GetDirection() * passTime * data_->GetMoveSpeed()->GetArrayValueByIndex(level - 1)->GetValue<float>();
    TARGET_LIST ret;
    CTargetSearcher::FindEntitesInLine(ret,
                                       data_->GetCaster(),
                                       currentPosition + data_->GetLength()->GetArrayValueByIndex(level - 1)->GetValue<float>(),
                                       currentPosition + data_->GetLength()->GetArrayValueByIndex(level - 1)->GetValue<float>(),
                                       data_->GetWidth()->GetArrayValueByIndex(level - 1)->GetValue<float>(),
                                       data_->GetDirection().getRadian(),
                                       data_->GetTargetType()->GetTeams(),
                                       data_->GetTargetType()->GetTypes(),
                                       data_->GetTargetType()->GetFlags());
    for (auto target : ret) {
        if (hitTargets_.find(target) == hitTargets_.end())
            hitTargets_[target] = 1;
    }
    if (ret.size() > 0) data_->GetAbility()->ExecutEvent(EVENT_TYPE_ON_PROJECTILE_HIT);
}

void CLinearProjectile::Execute() {
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CLinearProjectile::Update), 1.f / 60);
}
