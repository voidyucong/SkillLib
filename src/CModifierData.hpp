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

class CModifierData {
    friend class CModifier;
public:
    CModifierData* Clone();

    // event
    void SetModifierEvent(MODIFIER_EVENT_TYPE type, CModifierEvent* event) { events_[type] = event; }
    CModifierEvent* GetModifierEvent(MODIFIER_EVENT_TYPE type) { return events_[type]; }
    std::map<MODIFIER_EVENT_TYPE, CModifierEvent*> GetAllEvent() { return events_; }

    // property
    void SetProperty(MODIFIER_ATTRIBUTES attribute, float value) { properties_[attribute] = value; }
    float GetProperty(MODIFIER_ATTRIBUTES attribute) { return properties_[attribute]; }
    std::map<MODIFIER_ATTRIBUTES, float> GetAllProperty() { return properties_; }

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
    float GetDuration() { return duration_; }
    float GetThinkInterval() { return thinkInterval_; }
    std::string GetTextureName() { return textureName_; }
    std::string GetEffectName() { return effectName_; }
    std::string GetModelName() { return modelName_; }
    std::string GetName() { return name_; }
    
    void SetIsMulti(bool value) { isMulti_ = value; }
    void SetIsPassive(bool value) { isPassive_ = value; }
    void SetIsHidden(bool value) { isHidden_ = value; }
    void SetIsBuff(bool value) { isBuff_ = value; }
    void SetIsDebuff(bool value) { isDebuff_ = value; }
    void SetIsPurgable(bool value) { isPurgable_ = value; }
    void SetMaxMulti(int value) { maxMulti_ = value; }
    void SetDuration(float value) { duration_ = value; }
    void SetThinkInterval(float value) { thinkInterval_ = value; }
    void SetTextureName(std::string value) { textureName_ = value; }
    void SetEffectName(std::string value) { effectName_ = value; }
    void SetModelName(std::string value) { modelName_ = value; }
    void SetName(std::string value) { name_ = value; }
    
private:
    bool isMulti_;      // 是否可叠加
    int maxMulti_;    // 最高叠加层数
    float duration_;    // 持续时间
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
    
    std::map<MODIFIER_EVENT_TYPE, CModifierEvent*> events_;  // 事件集合
    std::vector<COperate*> operators_;
    std::map<MODIFIER_ATTRIBUTES, float> properties_;
};

#endif /* CModifierData_hpp */
