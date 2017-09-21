//
//  CAbilityEntity.cpp
//  SkillLib
//
//  Created by yucong on 2017/8/31.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbilityEntity.hpp"
#include <assert.h>
#include "CModifier.h"
#include "CScheduleManager.h"

CAbilityEntity::CAbilityEntity()
: abilityContainer_(new CAbilityContainer())
, attacker_(0)
{
    
}

CAbilityEntity::~CAbilityEntity() {
    delete abilityContainer_;
    abilityContainer_ = 0;
    
    for (auto iter = buffs_.begin(); iter != buffs_.end(); iter++) {
        for (auto modifier : iter->second->sameModifiers) {
            delete modifier;
            modifier = NULL;
        }
        delete iter->second;
    }
    buffs_.clear();
    for (auto iter = debuffs_.begin(); iter != debuffs_.end(); iter++) {
        for (auto modifier : iter->second->sameModifiers) {
            delete modifier;
            modifier = NULL;
        }
        delete iter->second;
    }
    debuffs_.clear();
    
}

void CAbilityEntity::Update(float dt) {
    // 移除无效的buff
    for (auto iter = buffs_.begin(); iter != buffs_.end(); ++iter) {
        for (auto miter = iter->second->sameModifiers.begin(); miter != iter->second->sameModifiers.end();) {
            auto modifier = *miter;
            if (modifier->IsWaitDestroy()) {
                iter->second->sameModifiers.erase(miter);
                modifier->Destroy();
            }
            else {
                ++miter;
            }
        }
    }
}

void CAbilityEntity::Destroy() {
    CScheduleManager::getInstance()->RemoveSchedule(this);
}

void CAbilityEntity::Execute() {
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CAbilityEntity::Update), 1.f/60);
}

void CAbilityEntity::ExecuteAbility(unsigned index) {
    assert(index < abilityContainer_->GetAbilityLayout());
    auto ability = abilityContainer_->GetAbility(index);
    assert(ability);
    ability->Cast();
}


#pragma mark -
#pragma mark attributes
void CAbilityEntity::SetEntityAbility(CAbility* ability, unsigned index) {
    abilityContainer_->SetAbility(ability, index);
    ability->SetCaster(this);
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
    if (modifyAttributes_.find(attribute) != modifyAttributes_.end()) {
        modifyAttributes_[attribute] += value;
    } else {
        modifyAttributes_[attribute] = value;
    }
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

void CAbilityEntity::AddModifer(CModifier* modifier) {
    if (modifier) {
        std::map<std::string, ModifierNode*>* buff = NULL;
        if (modifier->IsBuff()) {
            buff = &buffs_;
        }
        else if (modifier->IsDebuff()) {
            buff = &debuffs_;
        }
        if (buff) {
            if (buff->find(modifier->GetName()) != buff->end()) {
                if (modifier->IsMulti()) {
                    ModifierNode* node = (*buff)[modifier->GetName()];
                    node->sameModifiers.push_back(modifier);
                }
            }
            else {
                ModifierNode* node = new ModifierNode();
                node->sameModifiers.push_back(modifier);
                (*buff)[modifier->GetName()] = node;
            }
        }
    }
}

void CAbilityEntity::RemoveModifier(CModifier* modifier) {
    std::map<std::string, ModifierNode*>* buff = NULL;
    if (modifier->IsBuff()) {
        buff = &buffs_;
    }
    else if (modifier->IsDebuff()) {
        buff = &debuffs_;
    }
    if (buff->find(modifier->GetName()) != buff->end()) {
        auto node = (*buff)[modifier->GetName()];
        for (auto iter = node->sameModifiers.begin(); iter != node->sameModifiers.end(); iter++) {
            if (*iter == modifier) {
                node->sameModifiers.erase(iter);
                if (node->sameModifiers.size() == 0) {
                    (*buff)[modifier->GetName()] = NULL;
                }
                break;
            }
        }
    }
//    modifier->Destroy();
//    modifier = NULL;
}

void CAbilityEntity::ClearModifier(std::string name) {
    if (buffs_.find(name) != buffs_.end()) {
        auto node = buffs_[name];
        for (auto modifier : node->sameModifiers) {
            modifier->Destroy();
        }
        buffs_.erase(name);
    }
    else if (debuffs_.find(name) != debuffs_.end()) {
        auto node = debuffs_[name];
        for (auto modifier : node->sameModifiers) {
            modifier->Destroy();
            modifier = NULL;
        }
        debuffs_.erase(name);
    }
}
