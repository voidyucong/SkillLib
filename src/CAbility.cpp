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
#include "CTargetSearchType.hpp"
#include "CModifierData.hpp"
#include "TimeUtil.h"
#include "CTargetSearcher.hpp"
#include "CTargetStack.hpp"

CAbility::CAbility()
: level_(1)
, cooldown_(0.f)
, elapsed_(0.f)
, isValid_(true)
{
    base.targetSearchType_ = new CTargetSearchType();
    base.castPoint_ = NULL;
    base.castRange_ = NULL;
    base.castRangeBuffer_ = NULL;
    base.cooldown_ = NULL;
    base.damage_ = NULL;
    base.manaCost_ = NULL;
    base.crystalCost_ = NULL;
    base.hpCost_ = NULL;
    base.channelTime_ = NULL;
    base.channelledManaCostPerSecond_ = NULL;
    
    targetStack_ = new CTargetStack();
}


CAbility::~CAbility() {
    // delete events
    for (auto iter = base.events_.begin(); iter != base.events_.end(); iter++) {
        delete iter->second;
    }
    base.events_.clear();
    
    // delete special value
    for (auto iter = base.specials_.begin(); iter != base.specials_.end(); iter++) {
        delete iter->second;
    }
    base.specials_.clear();
    
    if (targetStack_) {
        delete targetStack_;
        targetStack_ = 0;
    }
}

void CAbility::Update(float dt) {
    elapsed_ += dt;
    if (base.channelTime_) {
        float channelTime = 0.f;
        if (GetChannelTime()->IsArray()) channelTime = GetChannelTime()->GetArrayValueByIndex(level_ - 1)->GetValue<float>();
        else channelTime = GetChannelTime()->GetValue<float>();
        if (elapsed_ >= channelTime) {
            CScheduleManager::getInstance()->RemoveSchedule(this);
            std::cout << "技能释放结束" << std::endl;
        }
    }
}

void CAbility::Cast() {
    if (!isValid_) {
        return;
    }
    // check cd
    double now = SKB::TimeUtil::GetSeconds();
    std::cout << "cooldown:" << std::fixed << cooldown_ << " now:" << std::fixed << now << std::endl;
    if (cooldown_ > now) {
        std::cout << "冷却中 " << cooldown_ << std::endl;
        return;
    }
    
    // target
    HandleTargetStack();
    if ((base.behavior_ & ABILITY_BEHAVIOR_UNIT_TARGET) && targetStack_->GetSelf()->Size() == 0) {
        std::cout << "技能需要目标才能释放" << std::endl;
        return;
    }
    
    // check mana
//    float manacost = this->GetManaCost()->GetValue<float>();
//    if (manacost > 0) {
//        manacost *= (1 - this->GetModifyAttribute(MODIFIER_ATTRIBUTE_MANACOST_GAIN_PERCENT));
//        float currentMana = entity->GetCurrentAttribute(ENTITY_ATTRIBUTE_MANA);
//        if (currentMana < manacost) {
//            std::cout << "mana 不足. 需要" << manacost << " 拥有" << currentMana << std::endl;
//            return;
//        }
//        entity->ModifyAttribute(ENTITY_ATTRIBUTE_MANA, -manacost);
//    }
    // check crystal
//    float crystalcost = this->GetCrystalCost()->GetValue<float>();
//    if (crystalcost > 0) {
//        crystalcost *= (1 - this->GetModifyAttribute(MODIFIER_ATTRIBUTE_CRYSTALCOST_GAIN_PERCENT));
//        float currentCrystal = 10;  // 背包中查找
//        if (currentCrystal < crystalcost) {
//            return;
//        }
//    }
    
    // check hp
//    float hpcost = this->GetHpCost()->GetValue<float>();
//    if (hpcost > 0) {
//        hpcost *= (1 - this->GetModifyAttribute(MODIFIER_ATTRIBUTE_HPCOST_GAIN_PERCENT));
//        float currentHP = entity->GetCurrentAttribute(ENTITY_ATTRIBUTE_HP);
//        if (currentHP < hpcost) {
//            std::cout << "hp 不足. 需要" << hpcost << " 拥有" << currentHP << std::endl;
//            return;
//        }
//        entity->ModifyAttribute(ENTITY_ATTRIBUTE_HP, -hpcost);
//    }
    
    
    auto cooldown = this->GetLevelSpecialValueFor("cooldown", level_);
    cooldown_ = now + cooldown->GetValue<float>()
                * (1 - this->GetModifyAttribute(MODIFIER_ATTRIBUTE_COOLDOWN_GAIN_PERCENT))
                - this->GetModifyAttribute(MODIFIER_ATTRIBUTE_COOLDOWN_GAIN);
    
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CAbility::Update), 1/60);
    this->ExecutEvent(EVENT_TYPE_ON_SPELL_START);
}

void CAbility::HandleTargetStack() {
    if (!targetStack_->GetSelf()) {
        targetStack_->SetSelf(new CTargetStackItem());
    }
    auto item = targetStack_->GetSelf();
    CTargetSearcher::FindAbilityTargets(item->GetTargets(),
                                        caster_,
                                        caster_->GetPosition(),
                                        GetRadius() ? GetRadius()->GetArrayValueByIndex(level_ - 1) : NULL,
                                        GetTeams(),
                                        GetTypes(),
                                        GetFlags(),
                                        GetBehavior(),
                                        GetMaxTargets() ? GetMaxTargets()->GetArrayValueByIndex(level_ - 1) : NULL);
    
    for (auto target : targetStack_->GetValid()->GetTargets()) {
        std::cout << "Ability " << GetName() << " targets:" << target << std::endl;
    }
}


// events
void CAbility::SetEvent(EVENT_TYPE type, CEvent* event) {
    base.events_[type] = event;
}

int CAbility::ExecutEvent(EVENT_TYPE type) {
    CEvent* event = base.events_[type];
    if (not event) {
        return 0;
    }
    return event->Execute(caster_, this, targetStack_);
}


// special value

CAbilityValue* CAbility::GetLevelSpecialValueFor(std::string key, int level) {
    CAbilityValue* value = base.specials_[key];
    assert(value);
    return value->GetArrayValueByIndex(level - 1);
//    if (value->IsArray()) {
//        assert(value->GetValue<CAbilityValue::Array>().size() > level - 1);
//        return value->GetArrayValueByIndex(level - 1);
//        
//    }
//    else {
//        return value;
//    }
}


// attributes
void CAbility::ModifyAttribute(MODIFIER_ATTRIBUTES attribute, float value) {
    modifyAttributes_[attribute] = value;
}

float CAbility::GetModifyAttribute(MODIFIER_ATTRIBUTES attribute) {
    if (modifyAttributes_.find(attribute) == modifyAttributes_.end()) return 0.f;
    return modifyAttributes_[attribute];
}

// modifier
void CAbility::SetModifierData(std::string name, CModifierData* modifier) {
    modifierData_[name] = modifier;
}

CModifierData* CAbility::GetModifierData(std::string name) {
    return modifierData_[name];
}



//-------------------------------------------------------
