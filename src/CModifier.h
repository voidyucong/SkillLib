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

class CModifier : public CObject {
    typedef std::vector<CAbilityEntity*> COLLISION_TYPE;
public:
    CModifier();
    virtual ~CModifier();
    // 开始执行
    void Activate();
    void Activate(CAbilityEntity* caster, CAbility* ability);
    void Destroy();
    void Update(float dt);
    
    // properties处理
    void AddEntityProperty();
    void RemoveEntityProperty();
    
    int ExecuteEvent(MODIFIER_EVENT_TYPE type, CAbilityEntity *caster, CAbility *ability);
    void ExecuteOperate(CAbilityEntity* caster, CAbility* ability);
    
    // 所属的entity和ability
    void SetEntity(CAbilityEntity* caster) { caster_ = caster; }
    void SetAbility(CAbility* ability) { ability_ = ability; }
    
    // collision
    void AddCollision(CAbilityEntity* caster) { collisions_.push_back(caster); }
    COLLISION_TYPE GetAllCollisions() { return collisions_; }

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
    float GetDuration() { return modifierData_->duration_; }
    float GetThinkInterval() { return modifierData_->thinkInterval_; }
    std::string GetTextureName() { return modifierData_->textureName_; }
    std::string GetEffectName() { return modifierData_->effectName_; }
    std::string GetModelName() { return modifierData_->modelName_; }
    std::string GetName() { return modifierData_->name_; }
    
private:
    // 所属的entity和ability
    CAbilityEntity* caster_;
    CAbility* ability_;
    // 碰到的目标
    COLLISION_TYPE collisions_;
    // 原型数据
    CModifierData* modifierData_;
    // 存在的时间
    double spawnTime_;
    // 等待销毁
    bool isWaitDestroy_;
    //
    CTargetStack* targetStack_;
};

#endif /* CModifier_hpp */
