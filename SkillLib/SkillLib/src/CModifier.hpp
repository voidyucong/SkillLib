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

class CModifierEvent;

enum MODIFIER_EVENTS{
    MODIFIER_EVENT_ON_CREATED,              // 创建时
    MODIFIER_EVENT_ON_DESTROY,              // 销毁时
    MODIFIER_EVENT_ON_ATTACK,               // 攻击时
    MODIFIER_EVENT_ON_ATTACKED,             // 被攻击时
    MODIFIER_EVENT_ON_ATTACK_LADNED,        // 攻击到时
    MODIFIER_EVENT_ON_ATTACK_FAILED,        // 攻击单位丢失时
    MODIFIER_EVENT_ON_ATTACK_ALLIED,        // 攻击同盟时
    MODIFIER_EVENT_ON_DEAL_DAMAGE,          // 施加伤害时
    MODIFIER_EVENT_ON_TAKE_DAMAGE,          // 收到伤害时
    MODIFIER_EVENT_ON_DEATH,                // 死亡时
    MODIFIER_EVENT_ON_KILL,                 // 杀死任意单位时
    MODIFIER_EVENT_ON_KILL_HERO,            // 杀死英雄时
    MODIFIER_EVENT_ON_RESPAWN,              // 重生时
    MODIFIER_EVENT_ON_ORB,                  // 创建法球
    MODIFIER_EVENT_ON_ORB_FIRE,             // 法球发射时
    MODIFIER_EVENT_ON_ORB_IMPACT,           // 法球命中目标时
    MODIFIER_EVENT_ON_ABILITY_START,        // 施法开始时
    MODIFIER_EVENT_ON_ABILITY_EXECUTED,     // 施法结束时
    MODIFIER_EVENT_ON_HEAL_RECEIVED,        // 受到治疗时
    MODIFIER_EVENT_ON_HEALTH_GAINED,        // 主动获得生命值时
    MODIFIER_EVENT_ON_MANA_GAINED,          // 主动获得魔法值时
    MODIFIER_EVENT_ON_MANA_SPENT,           // 消耗魔法值时
    MODIFIER_EVENT_ON_ENTITY_MOVED,         // 移动时
    MODIFIER_EVENT_ON_TELEPORTED,           // 传送结束时
    MODIFIER_EVENT_ON_TELEPORTING,          // 传送开始时
    MODIFIER_EVENT_ON_PROJECTILE_DODGE,     // 躲避投射物时
    MODIFIER_EVENT_ON_INTERVAL,             // 定时器
};

class CModifier {
    
public:
    
    
    CModifier();
    virtual ~CModifier();
    
private:
    bool isMulti_;      // 是否可叠加
    float duration_;    // 持续时间
    bool isPassive_;    // 是否被动
    bool isHidden_;     // 是否隐藏图标
    bool isBuff_;       // 是否正面buff
    bool isDeBuff_;     // 是否负面buff
    bool isPurgable_;   // 是否可被清除
    float thinkInterval_;       // 间隔
    const char* textureName_;   // 图标名称
    const char* effectName_;    // 特效名
    const char* modelName_;     // 模型名，默认空
private:
    std::map<MODIFIER_EVENTS, CModifierEvent*> events_;  // 事件集合
};

#endif /* CModifier_hpp */
