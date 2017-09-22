//
//  CModifier.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifier.h"
#include "CModifierEvent.hpp"
#include "COperate.hpp"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CScheduleManager.h"
#include "TimeUtil.h"
#include "CTargetStack.hpp"

CModifier::CModifier()
: caster_(0)
, ability_(0)
, modifierData_(0)
, spawnTime_(0.f)
, isWaitDestroy_(false)
, targetStack_(new CTargetStack())
{
    
}

CModifier::~CModifier() {
    for (auto iter = modifierData_->events_.begin(); iter != modifierData_->events_.end(); iter++) {
        delete iter->second;
    }
    modifierData_->events_.clear();
    for (auto operate : modifierData_->operators_) {
        delete operate;
        operate = NULL;
    }
    modifierData_->operators_.clear();
    if (targetStack_) {
        delete targetStack_;
        targetStack_ = 0;
    }
    delete modifierData_;
    modifierData_ = 0;
}

void CModifier::Activate() {
    spawnTime_ = SKB::TimeUtil::GetSeconds();
    isWaitDestroy_ = false;
    if (caster_ && ability_) {
        ExecuteEvent(MODIFIER_EVENT_ON_CREATED, caster_, ability_);
        
        // 处理properties
        AddEntityProperty();
        
        if (modifierData_->GetThinkInterval() > 0)
            CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CModifier::Update), modifierData_->GetThinkInterval());
    }
}

void CModifier::Activate(CAbilityEntity* entity, CAbility* ability) {
    SetEntity(entity);
    SetAbility(ability);
    Activate();
}

void CModifier::Destroy() {
    ExecuteEvent(MODIFIER_EVENT_ON_DESTROY, caster_, ability_);
    spawnTime_ = 0.f;
    isWaitDestroy_ = false;
    RemoveEntityProperty();
    CScheduleManager::getInstance()->RemoveSchedule(this);
    delete this;
}

void CModifier::Update(float dt) {
//    std::cout << "CModifier Update" << std::endl;
    ExecuteEvent(MODIFIER_EVENT_ON_INTERVAL, caster_, ability_);
    if (spawnTime_ + modifierData_->GetDuration() < SKB::TimeUtil::GetSeconds()) {
        isWaitDestroy_ = true;  // 标记可销毁，由拥有的entity删除
    }
}


int CModifier::ExecuteEvent(MODIFIER_EVENT_TYPE type, CAbilityEntity *caster, CAbility *ability) {
    CModifierEvent* event = modifierData_->GetModifierEvent(type);
    if (event) {
        return event->Execute(caster, ability, targetStack_);
    }
    return 0;
}

void CModifier::ExecuteOperate(CAbilityEntity* caster, CAbility* ability) {
    for (COperate* operate : modifierData_->operators_) {
        operate->Execute(caster, ability, targetStack_);
    }
}

void CModifier::AddEntityProperty() {
    for (auto iter = modifierData_->properties_.begin(); iter != modifierData_->properties_.end(); ++iter) {
        caster_->ModifyAttribute((ENTITY_ATTRIBUTES)iter->first, iter->second);
        std::cout << "AddEntityProperty " << iter->first << " to " << caster_ << "," << " add value: " << iter->second << std::endl;
    }
}

void CModifier::RemoveEntityProperty() {
    for (auto iter = modifierData_->properties_.begin(); iter != modifierData_->properties_.end(); ++iter) {
        caster_->ModifyAttribute((ENTITY_ATTRIBUTES)iter->first, -iter->second);
        std::cout << "RemoveEntityProperty " << iter->first << " from " << caster_ << "," << " remove value: " << iter->second << std::endl;
    }
}

