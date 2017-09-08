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
#include "CObject.hpp"

class CEvent;
class CAbilityValue;
class CAbilityEntity;
class CModifier;
class CTargetSearcher;

class CAbility : public CObject {
    
public:
    CAbility();
    virtual ~CAbility();
    
    void Cast(CAbilityEntity* entity);
    void update(float dt);
    
    // attributes
    
    
    // events
    void SetEvent(EVENT_TYPE behavior, CEvent* event);
    int ExecutEvent(EVENT_TYPE behavior, CAbilityEntity* entity);
    
    
    // special value
    void SetSpecialValue(const char* key, CAbilityValue* value);
    CAbilityValue* GetLevelSpecialValueFor(const char* key, int level);
    
    void ModifyAttribute(ABILITY_ATTRIBUTES attribute, float value);
    float GetModifyAttribute(ABILITY_ATTRIBUTES attribute);
    
    // modifier
    void SetModifier(const char* name, CModifier* modifier);
    CModifier* GetModifier(const char* name);
    
    
    // set get
    void SetBehavior(int behavior) { behavior_ = behavior; }
    void SetDamageType(ABILITY_DAMAGE_TYPE type) { damageType_ = type; }
    void SetIsIgnoreSpellImmunity(bool ignore) { isIgnoreSpellImmunity_ = ignore; }
    void SetBeginLevel(int level) { beginLevel_ = level; }
    void SetStepLevel(int step) { stepLevel_ = step; }
    void SetTextureIconName(const char* name) { textureIconName_ = name; }
    void SetTargetType(CTargetSearcher* searcher) { targetSearcher_ = searcher; }
    void SetCastPoint(CAbilityValue* castPoint) { castPoint_ = castPoint; }
    void SetCastRange(CAbilityValue* castRange) { castRange_ = castRange; }
    void SetCastRangeBuffer(CAbilityValue* castRangeBuffer) { castRangeBuffer_ = castRangeBuffer; }
    void SetDamage(CAbilityValue* damage) { damage_ = damage; }
    void SetManaCost(CAbilityValue* manaCost) { manaCost_ = manaCost; }
    void SetCrystalCost(CAbilityValue* crystalCost) { crystalCost_ = crystalCost; }
    void SetHpCost(CAbilityValue* hpCost) { hpCost_ = hpCost; }
    void SetChannelTime(CAbilityValue* channelTime) { channelTime_ = channelTime; }
    void SetChannelManaCostPerSecond(CAbilityValue* cost) { channelledManaCostPerSecond_ = cost; }
    
    int GetBehavior() { return behavior_; }
    ABILITY_DAMAGE_TYPE GetDamageType() { return damageType_; }
    bool GetIsIgnoreSpellImmunity() { return isIgnoreSpellImmunity_; }
    int GetBeginLevel() { return beginLevel_; }
    int GetStepLevel() { return stepLevel_; }
    const char* GetTextureIconName() { return textureIconName_; }
    CTargetSearcher* GetTargetSearcher() { return targetSearcher_; }
    CAbilityValue* GetCastPoint() { return castPoint_; }
    CAbilityValue* GetCastRange() { return castRange_; }
    CAbilityValue* GetCastRangeBuffer() { return castRangeBuffer_; }
    CAbilityValue* GetDamage() { return damage_; }
    CAbilityValue* GetManaCost() { return manaCost_; }
    CAbilityValue* GetCrystalCost() { return crystalCost_; }
    CAbilityValue* GetHpCost() { return hpCost_; }
    CAbilityValue* GetChannelTime() { return channelTime_; }
    CAbilityValue* GetChannelManaCostPerSecond() { return channelledManaCostPerSecond_; }
    

private:
    int behavior_;
    ABILITY_DAMAGE_TYPE damageType_;  // 伤害类型
    bool isIgnoreSpellImmunity_;      // 是否无视魔免
    unsigned int beginLevel_;   // 初始等级
    unsigned int stepLevel_;    // 每x级升一次
    const char* textureIconName_;   // 图标
    CTargetSearcher* targetSearcher_;   // 目标
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
    
    std::map<EVENT_TYPE, CEvent*> events_;
    std::map<const char*, CAbilityValue*> specials_;
    
private:
    int level_;
    float cooldown_;
    float elapsed_;
    bool isValid_;
    std::map<ABILITY_ATTRIBUTES, float> modifyAttributes_;
    std::map<const char*, CModifier*> modifiers_;
};

#endif /* CAbility_hpp */
