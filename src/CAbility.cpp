//
//  CAbility.cpp
//  SkillLib
//
//  Created by yucong on 2017/8/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbility.hpp"
#include <assert.h>
#include "CEvent.hpp"
#include "CAbilityValue.hpp"
#include "CAbilityEntity.hpp"
#include "CScheduleManager.h"
#include "CTargetSearcher.hpp"
#include "TimeUtil.h"

CAbility::CAbility()
: level_(1)
, cooldown_(SKB::GetNow())
, elapsed_(0.f)
, isValid_(true)
{
    
}


CAbility::~CAbility() {
    // delete events
    for (auto iter = events_.begin(); iter != events_.end(); iter++) {
        delete iter->second;
    }
    
    // delete special value
    for (auto iter = specials_.begin(); iter != specials_.end(); iter++) {
        delete iter->second;
    }
}

void CAbility::update(float dt) {
    elapsed_ += dt;
    if (elapsed_ >= GetChannelTime()->GetArrayValueByIndex(level_ - 1)->GetValue<float>()) {
        CScheduleManager::getInstance()->RemoveSchedule(this);
        std::cout << "技能释放结束" << std::endl;
        
    }
}

void CAbility::Cast(CAbilityEntity* entity) {
    if (!isValid_) {
        return;
    }
    // check cd
    if (cooldown_ < SKB::GetNow()) {
        std::cout << "冷却中 " << cooldown_ << "s" << std::endl;
        return;
    }
    
    // target
    if ((behavior_ & ABILITY_BEHAVIOR_UNIT_TARGET) && !targetSearcher_->IsHaveTargets(entity)) {
        std::cout << "技能需要目标才能释放" << std::endl;
        return;
    }
    
    // check mana
    float manacost = this->GetManaCost()->GetValue<float>();
    if (manacost > 0) {
        manacost *= (1 - this->GetModifyAttribute(ABILITY_ATTRIBUTES_MANACOST_GAIN_PERCENT));
        float currentMana = entity->GetCurrentAttribute(ENTITY_ATTRIBUTE_MANA);
        if (currentMana < manacost) {
            std::cout << "mana 不足. 需要" << manacost << " 拥有" << currentMana << std::endl;
            return;
        }
        entity->ModifyAttribute(ENTITY_ATTRIBUTE_MANA, -manacost);
    }
    // check crystal
    float crystalcost = this->GetCrystalCost()->GetValue<float>();
    if (crystalcost > 0) {
        crystalcost *= (1 - this->GetModifyAttribute(ABILITY_ATTRIBUTES_CRYSTALCOST_GAIN_PERCENT));
        float currentCrystal = 10;  // 背包中查找
        if (currentCrystal < crystalcost) {
            return;
        }
    }
    
    // check hp
    float hpcost = this->GetHpCost()->GetValue<float>();
    if (hpcost > 0) {
        hpcost *= (1 - this->GetModifyAttribute(ABILITY_ATTRIBUTES_HPCOST_GAIN_PERCENT));
        float currentHP = entity->GetCurrentAttribute(ENTITY_ATTRIBUTE_HP);
        if (currentHP < hpcost) {
            std::cout << "hp 不足. 需要" << hpcost << " 拥有" << currentHP << std::endl;
            return;
        }
        entity->ModifyAttribute(ENTITY_ATTRIBUTE_HP, -hpcost);
    }
    
    
    auto cooldown = this->GetLevelSpecialValueFor("cooldown", level_);
    cooldown_ = SKB::GetNow() + cooldown->GetValue<float>()
                * (1 - this->GetModifyAttribute(ABILITY_ATTRIBUTES_COOLDOWN_GAIN_PERCENT))
                - this->GetModifyAttribute(ABILITY_ATTRIBUTES_COOLDOWN_GAIN);
    
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CAbility::update), 1/60);
    this->ExecutEvent(EVENT_TYPE_ON_SPELL_START, entity);
}


// events
void CAbility::SetEvent(EVENT_TYPE type, CEvent* event) {
    events_[type] = event;
}

int CAbility::ExecutEvent(EVENT_TYPE type, CAbilityEntity* entity) {
    CEvent* event = events_[type];
    if (not event) {
        return 0;
    }
    return event->Execute(entity, this);
}


// special value
void CAbility::SetSpecialValue(const char* key, CAbilityValue* value) {
    specials_[key] = value;
}

CAbilityValue* CAbility::GetLevelSpecialValueFor(const char* key, int level) {
    assert(key);
    CAbilityValue* value = specials_[key];
    assert(value);
    assert(value->IsType<CAbilityValue::Array>());
    assert(value->GetValue<CAbilityValue::Array>().size() > level - 1);
    return value->GetArrayValueByIndex(level - 1);
}


// attributes
void CAbility::ModifyAttribute(ABILITY_ATTRIBUTES attribute, float value) {
    modifyAttributes_[attribute] = value;
}

float CAbility::GetModifyAttribute(ABILITY_ATTRIBUTES attribute) {
    if (modifyAttributes_.find(attribute) == modifyAttributes_.end()) return 0.f;
    return modifyAttributes_[attribute];
}

// modifier
void CAbility::SetModifier(const char* name, CModifier* modifier) {
    modifiers_[name] = modifier;
}

CModifier* CAbility::GetModifier(const char* name) {
    return modifiers_[name];
}



//-------------------------------------------------------
