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
#include "CTargetStack.hpp"

CLinearProjectile::CLinearProjectile()
: CLinearProjectile(0)
{}

CLinearProjectile::CLinearProjectile(CLinearProjectileData* data)
: data_(data)
, castTimestamp_(SKB::TimeUtil::GetSeconds())
, stack_(new CTargetStack())
{
}

CLinearProjectile::~CLinearProjectile()
{
    CScheduleManager::getInstance()->RemoveSchedule(this);
    hitTargets_.clear();
    if (stack_) delete stack_;
    stack_ = 0;
    if (targetType_) delete targetType_;
    targetType_ = 0;
}

void CLinearProjectile::Update(float dt) {
    // 碰撞检测
    DoCollision();
    // 范围检测
    if (RangeDetection())
        Destroy();
}

void CLinearProjectile::Execute() {
    stack_->SetParent(GetAbility()->GetTargetStack());
    CreateEffect();
    DoCollision();
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CLinearProjectile::Update), 1.f / 60);
}

void CLinearProjectile::Destroy() {
    delete this;
}

void CLinearProjectile::DoCollision() {
    if (CollisionDetection()) {
        GetAbility()->ExecutEvent(EVENT_TYPE_ON_PROJECTILE_HIT, stack_);
        if (data_->GetIsDeleteOnHit())
            Destroy();
    }
}

void CLinearProjectile::CreateEffect() {
    
}

bool CLinearProjectile::CollisionDetection() {
    CAbility* ability = GetAbility();
    int level = ability->GetLevel();
    double passTime = SKB::TimeUtil::GetSeconds() - castTimestamp_;
    CVector currentPosition = GetCastPosition() + GetDirection() * passTime * data_->GetMoveSpeed()->GetArrayValueByIndex(level - 1)->GetValue<float>();
    int maxTargets = 0;
    if (GetTargetType()->GetMaxTargets()) {
        maxTargets = GetTargetType()->GetMaxTargets()->GetArrayValueByIndex(level - 1)->GetValue<float>();
    }
    TARGET_LIST ret;
    CTargetSearcher::FindEntitesInLine(ret,
                                       GetCaster(),
                                       currentPosition,
                                       CVector(currentPosition.GetX() + data_->GetLength()->GetArrayValueByIndex(level - 1)->GetValue<float>(),
                                               currentPosition.GetY()),
                                       data_->GetStartRadius()->GetArrayValueByIndex(level - 1)->GetValue<float>(),
                                       GetDirection().getRadian(),
                                       GetTargetType()->GetTeams(),
                                       GetTargetType()->GetTypes(),
                                       GetTargetType()->GetFlags(),
                                       maxTargets);
    
    bool isHaveNew = false;
    stack_->ClearSelf();
    for (auto target : ret) {
        if (hitTargets_.find(target) == hitTargets_.end()) {
            hitTargets_.insert(target);
            stack_->PushSelf(target);
            isHaveNew = true;
        }
    }
    std::cout << "Linear Projectile Position x:" << currentPosition.GetX() << " y:" << currentPosition.GetY() << std::endl;
    return isHaveNew;
}

bool CLinearProjectile::RangeDetection() {
    CAbility* ability = GetAbility();
    int level = ability->GetLevel();
    double passTime = SKB::TimeUtil::GetSeconds() - castTimestamp_;
    CVector currentPosition = GetCastPosition() + GetDirection() * passTime * data_->GetMoveSpeed()->GetArrayValueByIndex(level - 1)->GetValue<float>();
//    std::cout << currentPosition.GetX() << " " << currentPosition.GetY() << std::endl;
    if (currentPosition.GetDistance(GetCastPosition()) > data_->GetCastRadius()->GetArrayValueByIndex(level - 1)->GetValue<float>()) {
        std::cout << "Linear Projectile "  << this << " Out of range" << std::endl;
        return true;
    }
    return false;
}



CLinearProjectileData::~CLinearProjectileData() {
    if (moveSpeed_) delete moveSpeed_;
    moveSpeed_ = 0;
    if (startRadius_) delete startRadius_;
    startRadius_ = 0;
    if (endRadius_) delete endRadius_;
    endRadius_ = 0;
    if (length_) delete length_;
    length_ = 0;
    if (castRadius_) delete castRadius_;
    castRadius_ = 0;
    if (visionRadius_) delete visionRadius_;
    visionRadius_ = 0;
}

CLinearProjectileData* CLinearProjectileData::Clone() {
    CLinearProjectileData* data = new CLinearProjectileData();
    data->effectName_ = this->effectName_;
    data->moveSpeed_ = this->moveSpeed_->Clone();
    data->startRadius_ = this->startRadius_->Clone();
    data->endRadius_ = this->endRadius_->Clone();
    data->length_ = this->length_->Clone();
    data->castRadius_ = this->castRadius_->Clone();
    data->attachType_ = this->attachType_;
    data->isDeleteOnHit_ = this->isDeleteOnHit_;
    data->isProvidesVision_ = this->isProvidesVision_;
    if (this->visionRadius_)
        data->visionRadius_ = this->visionRadius_->Clone();
    return data;
}
