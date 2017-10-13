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
#include "SkillReaderJson.hpp"
#include "CTargetStack.hpp"
#include "CAura.hpp"
#include "CSkillCastIndicator.hpp"

CAbilityEntity::CAbilityEntity()
: abilityContainer_(new CAbilityContainer())
, attacker_(0)
{
    
}

CAbilityEntity::~CAbilityEntity() {
    delete abilityContainer_;
    abilityContainer_ = 0;
    
    for (auto iter = modifiers_.begin(); iter != modifiers_.end(); iter++) {
        for (auto modifier : iter->second->sameModifiers) {
            delete modifier;
            modifier = NULL;
        }
        delete iter->second;
    }
    modifiers_.clear();
    
}

void CAbilityEntity::Update(float dt) {
    // 移除无效的buff
    for (auto iter = modifiers_.begin(); iter != modifiers_.end(); ++iter) {
        for (auto miter = iter->second->sameModifiers.begin(); miter != iter->second->sameModifiers.end();) {
            auto modifier = *miter;
            if (modifier->IsWaitDestroy()) {
                std::cout << "RemoveModifier Target:" << this << " Modifier:" << modifier->GetName() << modifier << std::endl;
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

void CAbilityEntity::ExecuteAbilityEvent(EVENT_TYPE type) {
    for (int i = 0; i < abilityContainer_->GetAbilityLayout(); ++i) {
        auto ability = abilityContainer_->GetAbility(i);
        if (ability) ability->ExecutEvent(type);
    }
}

void CAbilityEntity::ExecuteModifierEvent(MODIFIER_EVENT_TYPE type) {
    for (auto iter = modifiers_.begin(); iter != modifiers_.end(); ++iter) {
        for (int i = 0; i < iter->second->sameModifiers.size(); ++i) {
            iter->second->sameModifiers[i]->ExecuteEvent(type);
        }
    }
}

void CAbilityEntity::SetData(CAbilityEntityData* data) {
    data_ = data;
    SetEntityAbilityLayout(data_->GetAbilityLayout());
    for (int i = 0; i < data_->GetAbilityLayout(); ++i) {
        char path[200];
        sprintf(path, "/Users/yucong/Documents/SkillLib/SkillLib/res/scripts/abilities/%s.json", data_->GetAbility(i).c_str());
        std::cout << "Parse Ability " << path << std::endl;
        CAbility* ability = SkillReaderJson::getInstance()->AbilityFromFile(path);
        SetEntityAbility(ability, i);
    }
    SetCurrentLevel(data_->GetLevel());
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
    data_->SetBaseAttributes(attribute, value);
}

void CAbilityEntity::ModifyAttribute(ENTITY_ATTRIBUTES attribute, float value) {
    if (modifyAttributes_.find(attribute) != modifyAttributes_.end()) {
        modifyAttributes_[attribute] += value;
    } else {
        modifyAttributes_[attribute] = value;
    }
}

float CAbilityEntity::GetBaseAttribute(ENTITY_ATTRIBUTES attribute) {
    return data_->GetAttributes(attribute);
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

void CAbilityEntity::AddModifier(CModifier* modifier) {
    if (modifier) {
        std::cout << "AddModifier Target:" << this << " Modifier:" << modifier->GetName() << modifier << std::endl;
        if (HasModifier(modifier->GetName())) {
            ModifierNode* node = modifiers_[modifier->GetName()];
            // 可叠加
            if (modifier->IsMulti()) {
                node->sameModifiers.push_back(modifier);
            }
            // 替换现存的
            else {
                if (node->sameModifiers.size() > 0) node->sameModifiers[0]->Destroy();
                node->sameModifiers.clear();
                node->sameModifiers.push_back(modifier);
            }
        }
        else {
            ModifierNode* node = new ModifierNode();
            node->sameModifiers.push_back(modifier);
            modifiers_[modifier->GetName()] = node;
        }
    }
}

void CAbilityEntity::AddModifier(CAbilityEntity* caster, CAbility* ability, std::string modifierName, CTargetStack* stack) {
    auto modifierData = ability->GetModifierData(modifierName);
    assert(modifierData);
    CModifier* modifier = new CModifier();
    modifier->SetModifierData(modifierData->Clone());
    modifier->GetTargetStack()->SetParent(stack);   // 保存父目标栈
    modifier->GetTargetStack()->PushSelf(this);     // 将当前目标添加到自己目标栈
    modifier->SetCaster(caster);
    // aura
    if (modifierData->GetAura() != "") {
        CAura* aura = new CAura(modifierData->GetAura(),
                                modifierData->GetDuration()->GetValue<float>(ability->GetLevel()),
                                CSkillCastIndicator::getInstance()->GetPoint(),
                                modifierData->GetAuraRadius()->GetValue<float>(ability->GetLevel()),
                                modifierData->GetAuraTargetType());
        aura->SetCaster(caster);
        aura->SetAbility(ability);
        modifier->SetAura(aura);
    }
    AddModifier(modifier);
    modifier->Activate(this, ability);
}

const std::map<std::string, ModifierNode*>& CAbilityEntity::GetModifiers() {
    return modifiers_;
}

void CAbilityEntity::RemoveModifier(CModifier* modifier) {
    if (HasModifier(modifier->GetName())) {
        ModifierNode* node = modifiers_[modifier->GetName()];
        for (auto iter = node->sameModifiers.begin(); iter != node->sameModifiers.end(); iter++) {
            if (*iter == modifier) {
                node->sameModifiers.erase(iter);
                modifier->Destroy();
                if (node->sameModifiers.empty()) {
                    modifiers_.erase(modifier->GetName());
                }
                break;
            }
        }
    }
}

void CAbilityEntity::RemoveModifier(std::string name) {
    if (HasModifier(name)) {
        ModifierNode* node = modifiers_[name];
        for (auto iter = node->sameModifiers.begin(); iter != node->sameModifiers.end(); iter++) {
            (*iter)->Destroy();
        }
        modifiers_.erase(name);
    }
}

void CAbilityEntity::ClearModifier(std::string name) {
    if (HasModifier(name)) {
        ModifierNode* node = modifiers_[name];
        for (auto modifier : node->sameModifiers) {
//            modifier->Destroy();
            RemoveModifier(modifier);
        }
//        buffs_.erase(name);
    }
}

bool CAbilityEntity::HasModifier(std::string name) {
    return modifiers_.find(name) != modifiers_.end();
}
