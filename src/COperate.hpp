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
#include "SkillTypes.h"
#include "CObject.hpp"

class CEvent;
class CTargetSearcher;
class CAbility;
class CAbilityEntity;
class CAbilityValue;
class CRunScprite;

class COperate : public CObject {
protected:
    CTargetSearcher* targetSearcher_;
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability);
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
    
    COperate();
    virtual ~COperate();
};

/**
 * 添加技能
 */
class COpAddAbility : public COperate {
    
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    COpBlink();
    ~COpBlink();
};

/**
 * 创建计时器
 */
class COpCreateThinker : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    COpDamage();
    ~COpDamage();
private:
    ABILITY_DAMAGE_TYPE damageType_;
    float damage_;      // 伤害
    float currentHealthPercentBasedDamage_;  //  基于当前生命百分比伤害
    float maxHealthPercentBasedDamage_;     // 基于最大生命百分比伤害
};

/**
 * 延迟
 */
class COpDelayedAction : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    COpLinearProjectile();
    ~COpLinearProjectile();
private:
    std::string effectName_;
    float moveSpeed_;
    unsigned startPosition_;
    bool isProvidesVision_;     // 是否提供视野
    float visionRadius_;        // 视野范围
};

/**
 * 创建追踪抛射物
 */
class COpTrackingProjectile : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    COpTrackingProjectile();
    ~COpTrackingProjectile();
private:
    std::string effectName_;
    float moveSpeed_;
    unsigned startPosition_;
    bool isProvidesVision_;     // 是否提供视野
    float visionRadius_;        // 视野范围
};

/**
 * 概率
 */
class COpRandom : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
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
    virtual int Execute(CAbilityEntity* entity, CAbility* ability);
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
