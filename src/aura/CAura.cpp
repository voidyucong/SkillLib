//
//  CAura.cpp
//  SkillLib
//
//  Created by yucong on 2017/10/12.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAura.hpp"
#include "CScheduleManager.h"
#include "CTargetSearchType.hpp"
#include "CTargetSearcher.hpp"
#include "TimeUtil.h"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CAbilityValue.hpp"


CAura::CAura() {
    
}

CAura::CAura(std::string modifierName, float duration, const CVector& position, float radius, CTargetSearchType* targetType)
: modifierName_(modifierName)
, duration_(duration)
, position_(position)
, radius_(radius)
, targetType_(targetType)
, endTime_(0.f)
{
    
}

CAura::~CAura() {
    
}

void CAura::Update(float dt) {
    if (SKB::TimeUtil::GetSeconds() >= endTime_) {
//        Destroy();
        return;
    }
    CCircle circle(position_, radius_);
    // 查看历史目标是否还在范围内
    for (auto iter = targets_.begin(); iter != targets_.end();) {
        CAbilityEntity* target = *iter;
        if (!circle.IntersectsPoint(target->GetPosition())) {
            target->RemoveModifier(modifierName_);
            iter = targets_.erase(iter);
        }
        else {
            ++iter;
        }
    }
    // 查找范围内的目标添加 modifier
    TARGET_LIST ret;
    CTargetSearcher::FindEntitesInRadius(ret,
                                         caster_,
                                         circle,
                                         targetType_->GetTeams(),
                                         targetType_->GetTypes(),
                                         targetType_->GetFlags(),
                                         targetType_->GetMaxTargets() ? targetType_->GetMaxTargets()->GetValue<float>(ability_->GetLevel()) : -1);
    for (auto target : ret) {
        if (!target->HasModifier(modifierName_)) {
            target->AddModifier(caster_, ability_, modifierName_);
            targets_.insert(target);
        }
    }
}

void CAura::Activate() {
    endTime_ = SKB::TimeUtil::GetSeconds() + duration_;
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CAura::Update), 1 / 60.f);
}

void CAura::Destroy() {
    std::cout << "Remove Aura " << modifierName_ << this << std::endl;
    // 清除所有目标的 modifier
    CCircle circle(position_, radius_);
    for (auto iter = targets_.begin(); iter != targets_.end(); ++iter) {
        CAbilityEntity* target = *iter;
        target->RemoveModifier(modifierName_);
    }
    targets_.clear();
    
    CScheduleManager::getInstance()->RemoveSchedule(this);
    delete this;
}
