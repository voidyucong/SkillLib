//
//  CAbility.hpp
//  SkillLib
//
//  Created by yucong on 2017/8/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbility_hpp
#define CAbility_hpp

#include <vector>
#include <map>
#include "SkillTypes.h"

#define SET_GET(variable) \


class CEvent;
class CTargetType;
class CAbilityValue;


class CAbility {
    
public:
    CAbility();
    ~CAbility();
    
    void Cast();
    
    // attributes
    
    
    // events
    void SetEvent(EVENT_TYPE behavior, CEvent* event);
    int ExecutEvent(EVENT_TYPE behavior);
    
    
    // special value
    void SetSpecialValue(const char* key, CAbilityValue* value);
    CAbilityValue* GetLevelSpecialValueFor(const char* key, int level);
    
    ABILITY_BEHAVIOR GetBehavior() { return behavior_; }
    CTargetType* GetTargetType() { return targetType_; }
    
    
    // set get
    void SetBehavior(ABILITY_BEHAVIOR behavior) { behavior_ = behavior; }
    void SetDamageType(ABILITY_DAMAGE_TYPE type) { damageType_ = type; }
    void SetIsIgnoreSpellImmunity(bool ignore) { isIgnoreSpellImmunity_ = ignore; }
    void SetBeginLevel(int level) { beginLevel_ = level; }
    void SetStepLevel(int step) { stepLevel_ = step; }
    void SetTextureIconName(const char* name) { textureIconName_ = name; }
    void SetTargetType(CTargetType* type) { targetType_ = type; }
    void SetCastPoint(CAbilityValue* castPoint) { castPoint_ = castPoint; }
    void SetCastRange(CAbilityValue* castRange) { castRange_ = castRange; }
    void SetCastRangeBuffer(CAbilityValue* castRangeBuffer) { castRangeBuffer_ = castRangeBuffer; }
    void SetDamage(CAbilityValue* damage) { damage_ = damage; }
    void SetManaCost(CAbilityValue* manaCost) { manaCost_ = manaCost; }
    void SetCrystalCost(CAbilityValue* crystalCost) { crystalCost_ = crystalCost; }
    void SetHpCost(CAbilityValue* hpCost) { hpCost_ = hpCost; }
    void SetChannelTime(CAbilityValue* channelTime) { channelTime_ = channelTime; }
    void SetChannelManaCostPerSecond(CAbilityValue* cost) { channelledManaCostPerSecond_ = cost; }
    void SetDuration(CAbilityValue* duration) { duration_ = duration; }
    
    ABILITY_BEHAVIOR GetBehavior(ABILITY_BEHAVIOR behavior) { return behavior_; }
    ABILITY_DAMAGE_TYPE GetDamageType(ABILITY_DAMAGE_TYPE type) { return damageType_; }
    bool GetIsIgnoreSpellImmunity(bool ignore) { return isIgnoreSpellImmunity_; }
    int GetBeginLevel(int level) { return beginLevel_; }
    int GetStepLevel(int step) { return stepLevel_; }
    const char* GetTextureIconName(const char* name) { return textureIconName_; }
    CTargetType* GetTargetType(CTargetType* type) { return targetType_; }
    CAbilityValue* GetCastPoint(CAbilityValue* castPoint) { return castPoint_; }
    CAbilityValue* GetCastRange(CAbilityValue* castRange) { return castRange_; }
    CAbilityValue* GetCastRangeBuffer(CAbilityValue* castRangeBuffer) { return castRangeBuffer_; }
    CAbilityValue* GetDamage(CAbilityValue* damage) { return damage_; }
    CAbilityValue* GetManaCost(CAbilityValue* manaCost) { return manaCost_; }
    CAbilityValue* GetCrystalCost(CAbilityValue* crystalCost) { return crystalCost_; }
    CAbilityValue* GetHpCost(CAbilityValue* hpCost) { return hpCost_; }
    CAbilityValue* GetChannelTime(CAbilityValue* channelTime) { return channelTime_; }
    CAbilityValue* GetChannelManaCostPerSecond(CAbilityValue* cost) { return channelledManaCostPerSecond_; }
    CAbilityValue* GetDuration(CAbilityValue* duration) { return duration_; }
    

private:
    ABILITY_BEHAVIOR behavior_;
    ABILITY_DAMAGE_TYPE damageType_;  // 伤害类型
    bool isIgnoreSpellImmunity_;      // 是否无视魔免
    unsigned int beginLevel_;   // 初始等级
    unsigned int stepLevel_;    // 每x级升一次
    const char* textureIconName_;   // 图标
    CTargetType* targetType_;   // 目标
    CAbilityValue* castPoint_;  // 施法前摇时间
    CAbilityValue* castRange_;  // 技能释放范围
    CAbilityValue* castRangeBuffer_;    // 释放范围缓冲，当 castRange_ < 目标 < castRangeBuffer_也会自己攻击
    CAbilityValue* damage_;     // 伤害
    CAbilityValue* manaCost_;   // 法术消耗
    CAbilityValue* crystalCost_;// 晶石消耗
    CAbilityValue* hpCost_;     // 血量消耗
    
    // 需要behavier包含 ABILITY_BEHAVIOR_CHANNELLED
    CAbilityValue* channelTime_;    // 持续施法时间
    CAbilityValue* channelledManaCostPerSecond_;    // 持续施法每秒的法术消耗
    
    CAbilityValue* duration_;   // 技能持续时间
    
    
    std::map<EVENT_TYPE, CEvent*> events_;
    
    std::map<const char*, CAbilityValue*> specials_;
};

#endif /* CAbility_hpp */
