//
//  CModifierData.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/14.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CModifierData_hpp
#define CModifierData_hpp

#include <iostream>
#include <map>
#include <vector>
#include "SkillTypes.h"

class CModifierEvent;
class COperate;
class CAbility;
class CAbilityEntity;
class CModifier;
class CAbilityValue;
class CTargetSearchType;

class CModifierData {
    friend class CModifier;
public:
    CModifierData* Clone();

    // event
    void SetModifierEvent(MODIFIER_EVENT_TYPE type, CModifierEvent* event) { events_[type] = event; }
    CModifierEvent* GetModifierEvent(MODIFIER_EVENT_TYPE type) { return events_[type]; }
    std::map<MODIFIER_EVENT_TYPE, CModifierEvent*> GetAllEvent() { return events_; }
    bool IsPropertyUnique(MODIFIER_PROPERTY property) { return propertyUnique_[property]; }

    // property
    void SetProperty(MODIFIER_PROPERTY attribute, float value, bool isUnique = true) {
        properties_[attribute] = value;
        propertyUnique_[attribute] = isUnique;
    }
    float GetProperty(MODIFIER_PROPERTY attribute) { return properties_[attribute]; }
    std::map<MODIFIER_PROPERTY, float> GetAllProperty() { return properties_; }
    
    // state
    void SetStates(MODIFIER_STATE state, bool value) { states_[state] = value; }
    float GetStates(MODIFIER_STATE state) { return states_[state]; }
    std::map<MODIFIER_STATE, bool> GetAllStates() { return states_; }

    // opertate
    void AddOperate(COperate* operate) { operators_.push_back(operate); }
    std::vector<COperate*> GetAllOperate() { return operators_; }

    //
    bool IsMulti() { return isMulti_; }
    bool IsPassive() { return isPassive_; }
    bool IsHidden() { return isHidden_; }
    bool IsBuff() { return isBuff_; }
    bool IsDebuff() { return isDebuff_; }
    bool IsPurgable() { return isPurgable_; }
    int GetMaxMulti() { return maxMulti_; }
    CAbilityValue* GetDuration() { return duration_; }
    float GetThinkInterval() { return thinkInterval_; }
    std::string GetTextureName() { return textureName_; }
    std::string GetEffectName() { return effectName_; }
    std::string GetModelName() { return modelName_; }
    std::string GetName() { return name_; }
    MODIFIER_EFFECT_ATTACH_TYPE GetAttachType() { return attachType_; }
    std::string GetAura() { return aura_; }
    CAbilityValue* GetAuraRadius() { return auraRadius_; }
    CTargetSearchType* GetAuraTargetType() { return auraTargetType_; }
    
    void SetIsMulti(bool value) { isMulti_ = value; }
    void SetIsPassive(bool value) { isPassive_ = value; }
    void SetIsHidden(bool value) { isHidden_ = value; }
    void SetIsBuff(bool value) { isBuff_ = value; }
    void SetIsDebuff(bool value) { isDebuff_ = value; }
    void SetIsPurgable(bool value) { isPurgable_ = value; }
    void SetMaxMulti(int value) { maxMulti_ = value; }
    void SetDuration(CAbilityValue* value) { duration_ = value; }
    void SetThinkInterval(float value) { thinkInterval_ = value; }
    void SetTextureName(std::string value) { textureName_ = value; }
    void SetEffectName(std::string value) { effectName_ = value; }
    void SetModelName(std::string value) { modelName_ = value; }
    void SetName(std::string value) { name_ = value; }
    void SetAttachType(MODIFIER_EFFECT_ATTACH_TYPE type) { attachType_ = type; }
    void SetAura(std::string aura) { aura_ = aura; }
    void SetAuraRadius(CAbilityValue* radius) { auraRadius_ = radius; }
    void SetAuraTargetType(CTargetSearchType* type) { auraTargetType_ = type; }
    
private:
    bool isMulti_;      // 是否可叠加
    int maxMulti_;    // 最高叠加层数
    CAbilityValue* duration_;    // 持续时间
    bool isPassive_;    // 是否被动
    bool isHidden_;     // 是否隐藏图标
    bool isBuff_;       // 是否正面buff
    bool isDebuff_;     // 是否负面buff
    bool isPurgable_;   // 是否可被清除
    float thinkInterval_;       // 间隔
    std::string textureName_;   // 图标名称
    std::string effectName_;    // 特效名
    std::string modelName_;     // 模型名，默认空
    std::string name_;
    MODIFIER_EFFECT_ATTACH_TYPE attachType_;
    
    // aura
    std::string aura_;
    CAbilityValue* auraRadius_;
    CTargetSearchType* auraTargetType_;
    
    std::map<MODIFIER_EVENT_TYPE, CModifierEvent*> events_;  // 事件集合
    std::vector<COperate*> operators_;
    std::map<MODIFIER_PROPERTY, float> properties_;
    std::map<MODIFIER_PROPERTY, bool> propertyUnique_;
    std::map<MODIFIER_STATE, bool> states_;
};

#endif /* CModifierData_hpp */
