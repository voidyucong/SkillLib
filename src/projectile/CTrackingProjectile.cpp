//
//  CTrackingProjectile.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CTrackingProjectile.hpp"
#include "CAbilityValue.hpp"
#include "CTargetStack.hpp"
#include "TimeUtil.h"
#include "CScheduleManager.h"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CTargetSearcher.hpp"

CTrackingProjectile::CTrackingProjectile()
: CTrackingProjectile(0)
{
    
}

CTrackingProjectile::CTrackingProjectile(CTrackingProjectileData* data)
: data_(data)
, castTimestamp_(SKB::TimeUtil::GetSeconds())
, lastFrameTimestamp_(castTimestamp_)
, stack_(new CTargetStack())
{
    
}

CTrackingProjectile::~CTrackingProjectile() {
    std::cout << "CTrackingProjectile Destruct " << this << std::endl;
    CScheduleManager::getInstance()->RemoveSchedule(this);
    if (stack_) delete stack_;
    stack_ = 0;
}

void CTrackingProjectile::Update(float dt) {
    // 碰撞检测
    DoCollision();
}

void CTrackingProjectile::Execute() {
    stack_->SetParent(GetAbility()->GetTargetStack());
    CreateEffect();
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CTrackingProjectile::Update), 1.f / 60);
}

void CTrackingProjectile::Destroy() {
    std::cout << "CTrackingProjectile Destroy" << std::endl;
    delete this;
}

void CTrackingProjectile::DoCollision() {
    if (CollisionDetection()) {
        std::cout << "DoCollision Hit!" << std::endl;
        stack_->ClearSelf();
        stack_->PushSelf(GetTarget());
        GetAbility()->ExecutEvent(EVENT_TYPE_ON_PROJECTILE_HIT, stack_);
        Destroy();
    }
}

void CTrackingProjectile::CreateEffect() {
    
}

bool CTrackingProjectile::CollisionDetection() {
    CAbility* ability = GetAbility();
    int level = ability->GetLevel();
    double passTime = SKB::TimeUtil::GetSeconds() - lastFrameTimestamp_;
    // 飞行方向
    const CVector& targetPosition = GetTarget()->GetPosition();
    CVector direction = (targetPosition - currentPosition_).normalize();
    // 飞行弧度
    float radian = currentPosition_.getRadian(targetPosition);
    
//    CVector midpoint(currentPosition_.GetX() + data_->GetCollisionSize().width/2, currentPosition_.GetY());
    
    CRect projectileRect(data_->GetCollisionSize().width,
                         data_->GetCollisionSize().height,
                         CVector(currentPosition_.GetX(), currentPosition_.GetY() - data_->GetCollisionSize().height/2).rotateByAngle(currentPosition_, radian).GetX(),
                         CVector(currentPosition_.GetX(), currentPosition_.GetY() - data_->GetCollisionSize().height/2).rotateByAngle(currentPosition_, radian).GetY());
    CCircle targetCircle(GetTarget()->GetCollisionCenter(),
                         GetTarget()->GetData()->GetCollisionRadius());
    CCircle projectileCircle(projectileRect);
    projectileCircle.SetCenter(projectileCircle.GetCenter().rotateByAngle(currentPosition_, radian));
//    std::cout << "Tracking Projectile Position x:" << currentPosition_.GetX() << " y:" << currentPosition_.GetY() << std::endl;
//    std::cout << "Target Position x:" << targetPosition.GetX() << " y:" << targetPosition.GetY() << std::endl;
    
    currentPosition_ = currentPosition_ + direction * passTime * data_->GetMoveSpeed()->GetArrayValueByIndex(level - 1)->GetValue<float>();
    lastFrameTimestamp_ = SKB::TimeUtil::GetSeconds();
    if (targetCircle.IntersectsCircel(projectileCircle)) {
        /*
        printf("========================================\n"\
               "CCDrawNode* node4 = CCDrawNode::create();\n" \
               "node4->drawDot(ccp(%f,%f), %f, ccc4f(1, 0, 0, 1));\n" \
               "layer->addChild(node4);\n" \
               "\n" \
               "CCDrawNode* node5 = CCDrawNode::create();\n" \
               "node5->drawDot(ccp(%f,%f), %f, ccc4f(0, 1, 0, 1));\n" \
               "layer->addChild(node5);\n" \
               "\n" \
               "CCPoint origin(%f, %f);\n" \
               "CCSize size(%f, %f);\n" \
               "float radian = %f;\n" \
               "CCPoint pivot(%f, %f);\n" \
               "========================================\n",
               targetCircle.GetCenter().GetX(), targetCircle.GetCenter().GetY(), targetCircle.GetRadius(),
               projectileCircle.GetCenter().GetX(), projectileCircle.GetCenter().GetY(), projectileCircle.GetRadius(),
               projectileRect.GetOrigin().GetX(), projectileRect.GetOrigin().GetY(),
               projectileRect.GetSize().width, projectileRect.GetSize().height,
               radian,
               currentPosition_.GetX(), currentPosition_.GetY());
         */
    }
    return targetCircle.IntersectsCircel(projectileCircle);
}


CTrackingProjectileData::~CTrackingProjectileData() {
    if (moveSpeed_) delete moveSpeed_;
    moveSpeed_ = 0;
    if (visionRadius_) delete visionRadius_;
    visionRadius_ = 0;
}

CTrackingProjectileData* CTrackingProjectileData::Clone() {
    CTrackingProjectileData* data = new CTrackingProjectileData();
    data->effectName_ = this->effectName_;
    data->moveSpeed_ = this->moveSpeed_->Clone();
    data->collisionSize_ = this->collisionSize_;
    data->attachType_ = this->attachType_;
    data->isProvidesVision_ = this->isProvidesVision_;
    if (this->visionRadius_)
        data->visionRadius_ = this->visionRadius_->Clone();
    return data;
}
