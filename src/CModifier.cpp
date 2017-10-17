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
#include "CAura.hpp"
#include "CSkillCastIndicator.hpp"

CModifier::CModifier()
: caster_(0)
, entity_(0)
, ability_(0)
, modifierData_(0)
, spawnTime_(0.f)
, isWaitDestroy_(false)
, targetStack_(new CTargetStack())
, aura_(0)
{
    
}

CModifier::~CModifier() {
    if (targetStack_) {
        delete targetStack_;
        targetStack_ = 0;
    }
    
}

void CModifier::Activate() {
    spawnTime_ = SKB::TimeUtil::GetSeconds();
    isWaitDestroy_ = false;
    if (entity_ && ability_) {
        ExecuteEvent(MODIFIER_EVENT_ON_CREATED);
        
        // 处理properties states
        AddEntityProperty();
        AddEntityState();
        
        if (modifierData_->GetThinkInterval() > 0)
            CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CModifier::OnThinkInterval), modifierData_->GetThinkInterval());
        CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CModifier::Update), 1 / 60.f);
    }
}

void CModifier::Activate(CAbilityEntity* entity, CAbility* ability) {
    SetEntity(entity);
    SetAbility(ability);
    Activate();
    if (aura_) aura_->Activate();
}

void CModifier::Destroy() {
    if (aura_) aura_->Destroy();
    ExecuteEvent(MODIFIER_EVENT_ON_DESTROY);
    spawnTime_ = 0.f;
    isWaitDestroy_ = false;
    RemoveEntityProperty();
    RemoveEntityState();
    CScheduleManager::getInstance()->RemoveSchedule(this);
    delete this;
}

void CModifier::Update(float dt) {
    float duration = modifierData_->GetDuration()->GetValue<float>(ability_->GetLevel());
    // duration == -1 代表一直存在
    if (duration >= 0.f && spawnTime_ + duration < SKB::TimeUtil::GetSeconds()) {
        isWaitDestroy_ = true;  // 标记可销毁，由拥有的entity删除
    }
}

void CModifier::OnThinkInterval(float dt) {
    ExecuteEvent(MODIFIER_EVENT_ON_INTERVAL);
}

int CModifier::ExecuteEvent(MODIFIER_EVENT_TYPE type) {
    CModifierEvent* event = modifierData_->GetModifierEvent(type);
    if (event) {
        return event->Execute(caster_, ability_, targetStack_);
    }
    return 0;
}

void CModifier::ExecuteOperate() {
    for (COperate* operate : modifierData_->operators_) {
        operate->Execute(caster_, ability_, targetStack_);
    }
}

void CModifier::AddEntityProperty() {
    for (auto iter = modifierData_->properties_.begin(); iter != modifierData_->properties_.end(); ++iter) {
        // 如果是唯一，则替换，否则累加
        if (modifierData_->IsPropertyUnique(iter->first))
            entity_->SetProperties(iter->first, iter->second);
        else
            entity_->ModifyProperties(iter->first, iter->second);
        std::cout << "AddEntityProperty " << iter->first << " to " << entity_ << "," << " add value: " << iter->second << std::endl;
    }
}

void CModifier::RemoveEntityProperty() {
    for (auto iter = modifierData_->properties_.begin(); iter != modifierData_->properties_.end(); ++iter) {
        entity_->ModifyProperties(iter->first, -iter->second);
        std::cout << "RemoveEntityProperty " << iter->first << " from " << entity_ << "," << " remove value: " << iter->second << std::endl;
    }
}

void CModifier::AddEntityState() {
    for (auto iter = modifierData_->states_.begin(); iter != modifierData_->states_.end(); ++iter) {
        entity_->SetState(iter->first, iter->second);
        std::cout << "AddEntityState " << iter->first << " to " << entity_ << "," << " add value: " << iter->second << std::endl;
    }
}

void CModifier::RemoveEntityState() {
    for (auto iter = modifierData_->states_.begin(); iter != modifierData_->states_.end(); ++iter) {
        entity_->SetState(iter->first, !iter->second);
        std::cout << "RemoveEntityState " << iter->first << " to " << entity_ << "," << " remove value: " << !iter->second << std::endl;
    }
}

CAura* CModifier::CreateAura() {
    // aura
    if (modifierData_->GetAura() != "") {
        CAura* aura = new CAura(modifierData_->GetAura(),
                                modifierData_->GetDuration()->GetValue<float>(ability_->GetLevel()),
                                CSkillCastIndicator::getInstance()->GetPoint(),
                                modifierData_->GetAuraRadius()->GetValue<float>(ability_->GetLevel()),
                                modifierData_->GetAuraTargetType());
        aura->SetCaster(caster_);
        aura->SetAbility(ability_);
        SetAura(aura);
    }
    return aura_;
}
