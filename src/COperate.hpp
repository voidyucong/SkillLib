//
//  COperate.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef COperate_hpp
#define COperate_hpp
#include <iostream>
#include <assert.h>
#include <vector>
#include "SkillTypes.h"
#include "CObject.hpp"

class CEvent;
class CTargetSearchType;
class CAbility;
class CAbilityEntity;
class CAbilityValue;
class CRunScprite;
class CTargetStack;

class COperate : public CObject {
protected:
    CTargetSearchType* targetSearchType_;
    CTargetStack* targetStack_;
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    virtual void Update(float dt);
    virtual COperate* Clone();
    virtual COperate* CreateCloneInstance();
    virtual void CloneProperties(COperate* operate);
    
    void SetSingle(TARGET_CENTER single);
    TARGET_CENTER GetSingle();
    
    void SetCenter(TARGET_CENTER center);
    TARGET_CENTER GetCenter();
    
    void SetRadius(CAbilityValue* radius);
    CAbilityValue* GetRadius();
    
    void SetTeams(TARGET_TEAMS teams);
    TARGET_TEAMS GetTeams();
    
    void SetTypes(TARGET_TYPES types);
    TARGET_TYPES GetTypes();
    
    void SetFlags(TARGET_FLAGS flags);
    TARGET_FLAGS GetFlags();
    
    void SetMaxTargets(CAbilityValue* max);
    CAbilityValue* GetMaxTargets();
    
    void SetParentTargets(CTargetStack* parent);
    void SetSelfTargets(TARGET_LIST targets);
    
    COperate();
    virtual ~COperate();
};

/**
 * 添加技能
 */
class COpAddAbility : public COperate {
    
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpAddAbility();
    ~COpAddAbility();
private:
    std::string abilityName_;
};

/**
 * 目标执行模型动作
 */
class COpActOnTargets : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpActOnTargets();
    ~COpActOnTargets();
private:
    std::string modelName_;
};

/**
 * 应用modifier
 */
class COpApplyModifier : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpApplyModifier();
    COpApplyModifier(std::string modifierName);
    ~COpApplyModifier();
private:
    std::string modifierName_;
};

/**
 * 附加特效
 */
class COpAttachEffect : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpAttachEffect();
    ~COpAttachEffect();
private:
    unsigned int attachType_;
};

/**
 * 闪现
 */
class COpBlink : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpBlink();
    ~COpBlink();
};

/**
 * 创建计时器
 */
class COpCreateThinker : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpCreateThinker();
    COpCreateThinker(float interval, float duration);
    ~COpCreateThinker();
    
    virtual void Update(float dt);
private:
    float interval_;
    float duration_;  // 默认-1，代表永远不停
};

/**
 * 制造伤害
 */
class COpDamage : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpDamage();
    ~COpDamage();
    
    void SetDamageType(ABILITY_DAMAGE_TYPE type) { damageType_ = type; }
    void SetDamage(CAbilityValue* value) { damage_ = value; }
    void SetCurrentPercent(CAbilityValue* value) { currentHealthPercentBasedDamage_ = value; }
    void SetMaxPercent(CAbilityValue* value) { maxHealthPercentBasedDamage_ = value; }
private:
    ABILITY_DAMAGE_TYPE damageType_;
    CAbilityValue* damage_;      // 伤害
    CAbilityValue* currentHealthPercentBasedDamage_;  //  基于当前生命百分比伤害
    CAbilityValue* maxHealthPercentBasedDamage_;     // 基于最大生命百分比伤害
};

/**
 * 延迟
 */
class COpDelayedAction : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpDelayedAction();
    ~COpDelayedAction();
private:
    float delay_;
    COperate* action_;
};

/**
 * 播放特效
 */
class COpFireEffect : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpFireEffect();
    ~COpFireEffect();
private:
    std::string effectName_;
    unsigned int attackType_;
    
};

/**
 * 播放音效
 */
class COpFireSound : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpFireSound();
    ~COpFireSound();
private:
    std::string effectName_;
};

/**
 * 治疗
 */
class COpHeal : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    void SetHealAmount(float amount) { healAmount_ = amount; }
    
    COpHeal();
    COpHeal(float amount);
    ~COpHeal();
    virtual COperate* CreateCloneInstance();
    virtual void CloneProperties(COperate* operate);
private:
    float healAmount_;  // 治疗量
};

/**
 * 击退
 */
class COpKnockback : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpKnockback();
    ~COpKnockback();
private:
    float distance_;
    float height_;
    
};

/**
 * 升级技能
 */
class COpLevelUpAbility : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpLevelUpAbility();
    ~COpLevelUpAbility();
private:
    std::string abilityName_;
};

/**
 * 吸血
 */
class COpLifesteal : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpLifesteal();
    ~COpLifesteal();
private:
    float lifestealPercent_;    // 吸血比例
};

/**
 * 创建线性投射物
 */
class COpLinearProjectile : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpLinearProjectile();
    ~COpLinearProjectile();
    
    void SetEffectName(std::string name) { effectName_ = name; }
    void SetMoveSpeed(CAbilityValue* value) { moveSpeed_ = value; }
    void SetStartRadius(CAbilityValue* value) { startRadius_ = value; }
    void SetEndRadius(CAbilityValue* value) { endRadius_ = value; }
    void SetDistance(CAbilityValue* value) { distance_ = value; }
    void SetAttachType(MODIFIER_EFFECT_ATTACH_TYPE value) { attachType_ = value; }
    void SetIsProvidesVision(bool value) { isProvidesVision_ = value; }
    void SetVisionRadius(CAbilityValue* value) { visionRadius_ = value; }
private:
    std::string effectName_;
    CAbilityValue* moveSpeed_;
    CAbilityValue* startRadius_;
    CAbilityValue* endRadius_;
    CAbilityValue* distance_;
    MODIFIER_EFFECT_ATTACH_TYPE attachType_;
    bool isProvidesVision_;     // 是否提供视野
    CAbilityValue* visionRadius_;        // 视野范围
};

/**
 * 创建追踪抛射物
 */
class COpTrackingProjectile : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpTrackingProjectile();
    ~COpTrackingProjectile();
private:
    std::string effectName_;
    float moveSpeed_;           // 移动速度
    unsigned startPosition_;
    bool isProvidesVision_;     // 是否提供视野
    float visionRadius_;        // 视野范围
    MODIFIER_EFFECT_ATTACH_TYPE SourceAttachment_;          // 附着点
};

/**
 * 概率
 */
class COpRandom : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpRandom();
    ~COpRandom();
private:
    float chance_;  // 0 - 100
    CEvent* onSuccess_;
    CEvent* onFailed_;
};

/**
 * 移除技能
 */
class COpRemoveAbility : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpRemoveAbility();
    ~COpRemoveAbility();
private:
    std::string abilityName_;
};

/**
 * 移除modifier
 */
class COpRemoveModifier : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpRemoveModifier();
    ~COpRemoveModifier();
private:
    std::string modifierName_;
};

/**
 * 执行脚本
 */
class COpRunScript : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpRunScript();
    ~COpRunScript();
private:
    std::string scriptFile_;
    std::string function_;
};

/**
 * 生产单位
 */
class COpSpawnUnit : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpSpawnUnit();
    ~COpSpawnUnit();
private:
    std::string unitName_;
    unsigned int unitCount_;
    unsigned int unitLimit_;
    float spawnRadius_;
    float duration_;
};

/**
 * 眩晕
 */
class COpStun : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpStun();
    ~COpStun();
private:
    float duration_;
};

/**
 * 消耗法术值
 */
class COpSpendMana : public COperate{
public:
    int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    COpSpendMana();
    ~COpSpendMana();
private:
    unsigned int mana_;
};

/**
 * log
 */
class COpLog : public COperate {
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    std::string GetText() { return text_; }
    void SetText(std::string text) { text_ = text; }
    
    COpLog();
    COpLog(std::string text);
    ~COpLog();
    virtual COperate* CreateCloneInstance();
    virtual void CloneProperties(COperate* operate);
private:
    std::string text_;
};


#endif /* COperate_hpp */
