//
//  CModifier.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CModifier_hpp
#define CModifier_hpp

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
    
    CModifierEvent* GetModifierEvent(MODIFIER_EVENT_TYPE type) { return events_[type]; }
    
    int ExecuteEvent(MODIFIER_EVENT_TYPE type);
    
    void ExecuteOperate(CAbilityEntity* entity, CAbility* ability);
    
    bool IsMulti() { return isMulti_; }
    bool IsPassive() { return isPassive_; }
    bool IsHidden() { return isHidden_; }
    bool IsBuff() { return isBuff_; }
    bool IsDebuff() { return isDebuff_; }
    bool IsPurgable() { return isPurgable_; }
    int GetMaxMulti() { return maxMulti_; }
    float GetDuration() { return duration_; }
    float GetThinkInterval() { return thinkInterval_; }
    const char* GetTextureName() { return textureName_; }
    const char* GetEffectName() { return effectName_; }
    const char* GetModelName() { return modelName_; }
    const char* GetName() { return name_; }
    
    CModifier();
    virtual ~CModifier();
    void Destroy();
    
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
    const char* textureName_;   // 图标名称
    const char* effectName_;    // 特效名
    const char* modelName_;     // 模型名，默认空
    const char* name_;
private:
    std::map<MODIFIER_EVENT_TYPE, CModifierEvent*> events_;  // 事件集合
    std::vector<COperate*> operators_;
};

#endif /* CModifier_hpp */
