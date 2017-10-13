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
#include "CModifierData.hpp"

class CModifierEvent;
class COperate;
class CAbility;
class CAbilityEntity;
class CTargetStack;
class CAura;

class CModifier : public CObject {
public:
    CModifier();
    virtual ~CModifier();
    // 开始执行
    void Activate();
    void Activate(CAbilityEntity* entity, CAbility* ability);
    void Destroy();
    void Update(float dt);
    void OnThinkInterval(float dt);
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    
    // properties处理
    void AddEntityProperty();
    void RemoveEntityProperty();
    
    // states
    void AddEntityState();
    void RemoveEntityState();
    
    int ExecuteEvent(MODIFIER_EVENT_TYPE type);
    void ExecuteOperate();
    
    // 所属的entity和ability
    void SetEntity(CAbilityEntity* entity) { entity_ = entity; }
    void SetAbility(CAbility* ability) { ability_ = ability; }
    
    // collision
    void AddCollision(CAbilityEntity* caster) { collisions_.push_back(caster); }
    TARGET_LIST GetAllCollisions() { return collisions_; }

    void SetModifierData(CModifierData* data) { modifierData_ = data; }
    CModifierData* GetModifierData() { return modifierData_; }
    
    // 是否可销毁了
    bool IsWaitDestroy() { return isWaitDestroy_; }
    
    CTargetStack* GetTargetStack() { return targetStack_; }
    
    bool IsMulti() { return modifierData_->isMulti_; }
    bool IsPassive() { return modifierData_->isPassive_; }
    bool IsHidden() { return modifierData_->isHidden_; }
    bool IsBuff() { return modifierData_->isBuff_; }
    bool IsDebuff() { return modifierData_->isDebuff_; }
    bool IsPurgable() { return modifierData_->isPurgable_; }
    int GetMaxMulti() { return modifierData_->maxMulti_; }
    CAbilityValue* GetDuration() { return modifierData_->duration_; }
    float GetThinkInterval() { return modifierData_->thinkInterval_; }
    std::string GetTextureName() { return modifierData_->textureName_; }
    std::string GetEffectName() { return modifierData_->effectName_; }
    std::string GetModelName() { return modifierData_->modelName_; }
    std::string GetName() { return modifierData_->name_; }
    
    void SetAura(CAura* aura) { aura_ = aura; }
    CAura* GetAura() { return aura_; }
    
private:
    CAbilityEntity* caster_;
    // 所属的entity和ability
    CAbilityEntity* entity_;
    CAbility* ability_;
    // 碰到的目标
    TARGET_LIST collisions_;
    // 原型数据
    CModifierData* modifierData_;
    // 存在的时间
    double spawnTime_;
    // 等待销毁
    bool isWaitDestroy_;
    //
    CTargetStack* targetStack_;
    
    CAura* aura_;
};

#endif /* CModifier_hpp */
