//
//  CModifier.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CModifier_hpp
#define CModifier_hpp

#include <iostream>
#include <map>
#include <vector>
#include "CObject.hpp"
#include "SkillTypes.h"

class CModifierEvent;
class COperate;
class CAbility;
class CAbilityEntity;

class CModifier : public CObject {
    
public:
    void SetModifierEvent(MODIFIER_EVENT_TYPE type, CModifierEvent* event);
    CModifierEvent* GetModifierEvent(MODIFIER_EVENT_TYPE type) { return base.events_[type]; }
    
    void SetProperty(MODIFIER_ATTRIBUTES attribute, float value) { base.properties_[attribute] = value; }
    float GetProperty(MODIFIER_ATTRIBUTES attribute) { return base.properties_[attribute]; }
    
    void AddOperate(COperate* operate) { base.operators_.push_back(operate); }
    
    int ExecuteEvent(MODIFIER_EVENT_TYPE type, CAbilityEntity *entity, CAbility *ability);
    void ExecuteOperate(CAbilityEntity* entity, CAbility* ability);
    
    CModifier* Clone();
    
    // 
    bool IsMulti() { return base.isMulti_; }
    bool IsPassive() { return base.isPassive_; }
    bool IsHidden() { return base.isHidden_; }
    bool IsBuff() { return base.isBuff_; }
    bool IsDebuff() { return base.isDebuff_; }
    bool IsPurgable() { return base.isPurgable_; }
    int GetMaxMulti() { return base.maxMulti_; }
    float GetDuration() { return base.duration_; }
    float GetThinkInterval() { return base.thinkInterval_; }
    std::string GetTextureName() { return base.textureName_; }
    std::string GetEffectName() { return base.effectName_; }
    std::string GetModelName() { return base.modelName_; }
    std::string GetName() { return base.name_; }
    
    void SetIsMulti(bool value) { base.isMulti_ = value; }
    void SetIsPassive(bool value) { base.isPassive_ = value; }
    void SetIsHidden(bool value) { base.isHidden_ = value; }
    void SetIsBuff(bool value) { base.isBuff_ = value; }
    void SetIsDebuff(bool value) { base.isDebuff_ = value; }
    void SetIsPurgable(bool value) { base.isPurgable_ = value; }
    void SetMaxMulti(int value) { base.maxMulti_ = value; }
    void SetDuration(float value) { base.duration_ = value; }
    void SetThinkInterval(float value) { base.thinkInterval_ = value; }
    void SetTextureName(std::string value) { base.textureName_ = value; }
    void SetEffectName(std::string value) { base.effectName_ = value; }
    void SetModelName(std::string value) { base.modelName_ = value; }
    void SetName(std::string value) { base.name_ = value; }
    
    CModifier();
    virtual ~CModifier();
    void Destroy();
    
private:
    struct {
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
    } base;
    
};

#endif /* CModifier_hpp */
