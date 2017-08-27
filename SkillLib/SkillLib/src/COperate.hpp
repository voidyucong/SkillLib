//
//  COperate.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef COperate_hpp
#define COperate_hpp

class CEvent;
class CTargetType;

// 特效附着点类型
enum {
    MODIFIER_EFFECT_ATTACH_TYPE_ORIGIN,     //  原点
    MODIFIER_EFFECT_ATTACH_TYPE_HEAD,       //  头顶
};

// 伤害类型
enum ABILITY_DAMAGE_TYPE {
    ABILITY_DAMAGE_TYPE_PHYSICAL,
    ABILITY_DAMAGE_TYPE_MAGICAL,
    ABILITY_DAMAGE_TYPE_PURE,
};

class COperate {
    // CEntity* target_;
public:
    COperate();
    virtual ~COperate();
};

/**
 * 添加技能
 */
class COperateAddAbility : public COperate {
    
public:
    COperateAddAbility();
    ~COperateAddAbility();
private:
    const char* abilityName_;
};

/**
 * 目标执行模型动作
 */
class CActOnTargets : public COperate {
public:
    CActOnTargets();
    ~CActOnTargets();
private:
    const char* modelName_;
};

/**
 * 应用modifier
 */
class CApplyModifier : public COperate {
public:
    CApplyModifier();
    ~CApplyModifier();
private:
    const char* modifierName_;
};

/**
 * 附加特效
 */
class CAttachEffect : public COperate {
public:
    CAttachEffect();
    ~CAttachEffect();
private:
    unsigned int attachType_;
};

/**
 * 闪烁
 */
class CBlink : public COperate {
public:
    CBlink();
    ~CBlink();
};

/**
 * 创建计时器
 */
class CCreateThinker : public COperate {
public:
    CCreateThinker();
    ~CCreateThinker();
};

/**
 * 制造伤害
 */
class CDamage : public COperate {
public:
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
    CFireEffect();
    ~CFireEffect();
private:
    const char* effectName_;
    unsigned int attackType_;
    
};

/**
 * 播放音效
 */
class CFireSound : public COperate {
public:
    CFireSound();
    ~CFireSound();
private:
    const char* effectName_;
};

/**
 * 治疗
 */
class CHeal : public COperate {
public:
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
    CLevelUpAbility();
    ~CLevelUpAbility();
private:
    const char* abilityName_;
};

/**
 * 吸血
 */
class CLifesteal : public COperate {
public:
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
    CLinearProjectile();
    ~CLinearProjectile();
private:
    const char* effectName_;
    float moveSpeed_;
    unsigned startPosition_;
    CTargetType* targetType_;
    bool isProvidesVision_;     // 是否提供视野
    float visionRadius_;        // 视野范围
};

/**
 * 创建追踪抛射物
 */
class CTrackingProjectile : public COperate {
public:
    CTrackingProjectile();
    ~CTrackingProjectile();
private:
    const char* effectName_;
    float moveSpeed_;
    unsigned startPosition_;
    CTargetType* targetType_;
    bool isProvidesVision_;     // 是否提供视野
    float visionRadius_;        // 视野范围
};

/**
 * 概率
 */
class CRandom : public COperate {
public:
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
    CRemoveAbility();
    ~CRemoveAbility();
private:
    const char* abilityName_;
};

/**
 * 移除modifier
 */
class CRemoveModifier : public COperate {
public:
    CRemoveModifier();
    ~CRemoveModifier();
private:
    const char* modifierName_;
};

/**
 * 执行脚本
 */
class CRunScript : public COperate {
public:
    CRunScript();
    ~CRunScript();
private:
    const char* scriptFile_;
    const char* function_;
};

/**
 * 生产单位
 */
class CSpawnUnit : public COperate {
public:
    CSpawnUnit();
    ~CSpawnUnit();
private:
    const char* unitName_;
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
    CSpendMana();
    ~CSpendMana();
private:
    unsigned int mana_;
};


#endif /* COperate_hpp */
