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

class COperate : public CObject {
protected:
    CTargetSearcher* targetSearcher_;
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability);
    virtual void Update(float dt);
    virtual COperate* Clone();
    
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
class COperateAddAbility : public COperate {
    
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    COperateAddAbility();
    ~COperateAddAbility();
private:
    std::string abilityName_;
};

/**
 * 目标执行模型动作
 */
class CActOnTargets : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CActOnTargets();
    ~CActOnTargets();
private:
    std::string modelName_;
};

/**
 * 应用modifier
 */
class CApplyModifier : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CApplyModifier();
    CApplyModifier(std::string modifierName);
    ~CApplyModifier();
private:
    std::string modifierName_;
};

/**
 * 附加特效
 */
class CAttachEffect : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CAttachEffect();
    ~CAttachEffect();
private:
    unsigned int attachType_;
};

/**
 * 闪现
 */
class CBlink : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CBlink();
    ~CBlink();
};

/**
 * 创建计时器
 */
class CCreateThinker : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CCreateThinker();
    CCreateThinker(float interval, float duration);
    ~CCreateThinker();
    
    virtual void Update(float dt);
private:
    float interval_;
    float duration_;  // 默认-1，代表永远不停
};

/**
 * 制造伤害
 */
class CDamage : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CDamage();
    ~CDamage();
private:
    ABILITY_DAMAGE_TYPE damageType_;
    float damage_;      // 伤害
    float currentHealthPercentBasedDamage_;  //  基于当前生命百分比伤害
    float maxHealthPercentBasedDamage_;     // 基于最大生命百分比伤害
};

/**
 * 延迟
 */
class CDelayedAction : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CDelayedAction();
    ~CDelayedAction();
private:
    float delay_;
    COperate* action_;
};

/**
 * 播放特效
 */
class CFireEffect : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CFireEffect();
    ~CFireEffect();
private:
    std::string effectName_;
    unsigned int attackType_;
    
};

/**
 * 播放音效
 */
class CFireSound : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CFireSound();
    ~CFireSound();
private:
    std::string effectName_;
};

/**
 * 治疗
 */
class CHeal : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CHeal();
    ~CHeal();
private:
    float healAmount_;  // 治疗量
};

/**
 * 击退
 */
class CKnockback : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CKnockback();
    ~CKnockback();
private:
    float distance_;
    float height_;
    
};

/**
 * 升级技能
 */
class CLevelUpAbility : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CLevelUpAbility();
    ~CLevelUpAbility();
private:
    std::string abilityName_;
};

/**
 * 吸血
 */
class CLifesteal : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CLifesteal();
    ~CLifesteal();
private:
    float lifestealPercent_;    // 吸血比例
};

/**
 * 创建线性投射物
 */
class CLinearProjectile : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CLinearProjectile();
    ~CLinearProjectile();
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
class CTrackingProjectile : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CTrackingProjectile();
    ~CTrackingProjectile();
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
class CRandom : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CRandom();
    ~CRandom();
private:
    float chance_;  // 0 - 100
    CEvent* onSuccess_;
    CEvent* onFailed_;
};

/**
 * 移除技能
 */
class CRemoveAbility : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CRemoveAbility();
    ~CRemoveAbility();
private:
    std::string abilityName_;
};

/**
 * 移除modifier
 */
class CRemoveModifier : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CRemoveModifier();
    ~CRemoveModifier();
private:
    std::string modifierName_;
};

/**
 * 执行脚本
 */
class CRunScript : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CRunScript();
    ~CRunScript();
private:
    std::string scriptFile_;
    std::string function_;
};

/**
 * 生产单位
 */
class CSpawnUnit : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CSpawnUnit();
    ~CSpawnUnit();
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
class CStun : public COperate {
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CStun();
    ~CStun();
private:
    float duration_;
};

/**
 * 消耗法术值
 */
class CSpendMana : public COperate{
public:
    int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CSpendMana();
    ~CSpendMana();
private:
    unsigned int mana_;
};

/**
 * log
 */
class CLog : public COperate {
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability);
    void SetText(std::string text) { text_ = text; }
    
    CLog();
    CLog(std::string text);
    ~CLog();
private:
    std::string text_;
};


#endif /* COperate_hpp */
