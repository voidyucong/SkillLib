//
//  CAbilityEntity.cpp
//  SkillLib
//
//  Created by yucong on 2017/8/31.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbilityEntity.hpp"
#include <assert.h>

CAbilityEntity::CAbilityEntity()
: abilityContainer_(new CAbilityContainer())
{
    
}

CAbilityEntity::~CAbilityEntity() {
    delete abilityContainer_;
    abilityContainer_ = 0;
}

void CAbilityEntity::ExecuteAbility(unsigned index) {
    assert(index < abilityContainer_->GetAbilityLayout());
    abilityContainer_->GetAbility(index)->Cast();
}

void CAbilityEntity::SetEntityAbility(CAbility* ability, unsigned index) {
    abilityContainer_->SetAbility(ability, index);
}

void CAbilityEntity::SetEntityAbilityLayout(unsigned layout) {
    abilityContainer_->SetAbilityLayout(layout);
}

void CAbilityEntity::SetBaseAttribute(ENTITY_ATTRIBUTES attribute, float value) {
    assert(value);
    baseAttributes_[attribute] = value;
}

void CAbilityEntity::ModifyAttribute(ENTITY_ATTRIBUTES attribute, float value) {
    assert(value);
    modifyAttributes_[attribute] = value;
}

float CAbilityEntity::GetBaseAttribute(ENTITY_ATTRIBUTES attribute) {
    if (baseAttributes_.find(attribute) != baseAttributes_.end()) {
        return baseAttributes_[attribute];
    }
    return 0.f;
}

float CAbilityEntity::GetModifyAttribute(ENTITY_ATTRIBUTES attribute) {
    if (modifyAttributes_.find(attribute) != modifyAttributes_.end()) {
        return modifyAttributes_[attribute];
    }
    return 0.f;
}

float CAbilityEntity::GetCurrentAttribute(ENTITY_ATTRIBUTES attribute) {
    return this->GetBaseAttribute(attribute) + this->GetModifyAttribute(attribute);
}
