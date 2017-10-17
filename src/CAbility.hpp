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
#include "CTargetSearchType.hpp"

class CEvent;
class CAbilityValue;
class CAbilityEntity;
class CModifier;
class CModifierData;
class CTargetStack;

class CAbility : public CObject {
    typedef std::map<std::string, CAbilityValue*> SPECIAL_VALUE;
public:
    CAbility();
    virtual ~CAbility();
    void Update(float dt);
    void Cast();
    
    // attributes
    
    
    // events
    void SetEvent(EVENT_TYPE type, CEvent* event);
    int ExecutEvent(EVENT_TYPE type);
    int ExecutEvent(EVENT_TYPE type, CTargetStack* stack);
    
    // special value
    void AddSpecialValue(CAbilityValue* value, std::string name) { base.specials_[name] = value; }
    const SPECIAL_VALUE& GetSpecial() { return base.specials_; }
    CAbilityValue* GetSpecialValue(std::string name) { return base.specials_[name]; }
    CAbilityValue* GetLevelSpecialValueFor(std::string key, int level);
    bool IsSpecialValueExist(std::string name);
    
    void ModifyAttribute(ABILITY_ATTRIBUTE attribute, float value);
    float GetModifyAttribute(ABILITY_ATTRIBUTE attribute);
    
    // modifier
    void SetModifierData(std::string name, CModifierData* modifier);
    CModifierData* GetModifierData(std::string name);
    
    // 处理目标栈
    void HandleTargetStack();
    CTargetStack* GetTargetStack() { return targetStack_; }
    
    // set get
    void SetName(std::string name) { base.name_ = name; }
    void SetBehavior(long behavior) { base.behavior_ = behavior; }
    void SetDamageType(ABILITY_DAMAGE_TYPE type) { base.damageType_ = type; }
    void SetIsIgnoreSpellImmunity(bool ignore) { base.isIgnoreSpellImmunity_ = ignore; }
    void SetBeginLevel(int level) { base.beginLevel_ = level; }
    void SetStepLevel(int step) { base.stepLevel_ = step; }
    void SetMaxLevel(int max) { base.maxLevel_ = max; }
    void SetTextureIconName(std::string name) { base.textureIconName_ = name; }
    void SetCastPoint(CAbilityValue* castPoint) { base.castPoint_ = castPoint; }
    void SetCastWidth(CAbilityValue* castWidth) { base.castWidth_ = castWidth; }
    void SetCastRange(CAbilityValue* castRange) { base.castRange_ = castRange; }
    void SetCastRangeBuffer(CAbilityValue* castRangeBuffer) { base.castRangeBuffer_ = castRangeBuffer; }
    void SetAoeRange(CAbilityValue* range) { base.aoeRange_ = range; }
    void SetDamage(CAbilityValue* damage) { base.damage_ = damage; }
    void SetManaCost(CAbilityValue* manaCost) { base.manaCost_ = manaCost; }
    void SetCrystalCost(CAbilityValue* crystalCost) { base.crystalCost_ = crystalCost; }
    void SetHpCost(CAbilityValue* hpCost) { base.hpCost_ = hpCost; }
    void SetChannelTime(CAbilityValue* channelTime) { base.channelTime_ = channelTime; }
    void SetChannelManaCostPerSecond(CAbilityValue* cost) { base.channelledManaCostPerSecond_ = cost; }
    void SetBaseCooldown(CAbilityValue* value) { base.cooldown_ = value; }
    
    
    std::string GetName() { return base.name_.c_str(); }
    long GetBehavior() { return base.behavior_; }
    ABILITY_DAMAGE_TYPE GetDamageType() { return base.damageType_; }
    bool GetIsIgnoreSpellImmunity() { return base.isIgnoreSpellImmunity_; }
    int GetBeginLevel() { return base.beginLevel_; }
    int GetStepLevel() { return base.stepLevel_; }
    int GetMaxLevel() { return base.maxLevel_; }
    std::string GetTextureIconName() { return base.textureIconName_; }
    CAbilityValue* GetCastPoint() { return base.castPoint_; }
    CAbilityValue* GetCastWidth() { return base.castWidth_; }
    CAbilityValue* GetCastRange() { return base.castRange_; }
    CAbilityValue* GetCastRangeBuffer() { return base.castRangeBuffer_; }
    CAbilityValue* GetAoeRange() { return base.aoeRange_; }
    CAbilityValue* GetDamage() { return base.damage_; }
    CAbilityValue* GetManaCost() { return base.manaCost_; }
    CAbilityValue* GetCrystalCost() { return base.crystalCost_; }
    CAbilityValue* GetHpCost() { return base.hpCost_; }
    CAbilityValue* GetChannelTime() { return base.channelTime_; }
    CAbilityValue* GetChannelManaCostPerSecond() { return base.channelledManaCostPerSecond_; }
    CAbilityValue* GetBaseCooldown() { return base.cooldown_; }
    double GetCooldown() { return cooldown_; }
    
    // 获取实际的数值（有buff加成）
    float GetCurCastRange();
    float GetCurCastRangeBuffer();
    
    void SetCenter(TARGET_CENTER center) { base.targetSearchType_->SetCenter(center); }
    TARGET_CENTER GetCenter() { return base.targetSearchType_->GetCenter(); }
    
    void SetRadius(CAbilityValue* radius) { base.targetSearchType_->SetRadius(radius); }
    CAbilityValue* GetRadius() { return base.targetSearchType_->GetRadius(); }
    
    void SetTeams(TARGET_TEAMS teams) { base.targetSearchType_->SetTeams(teams); }
    TARGET_TEAMS GetTeams() { return base.targetSearchType_->GetTeams(); }
    
    void SetTypes(TARGET_TYPES types) { base.targetSearchType_->SetTypes(types); }
    TARGET_TYPES GetTypes() { return base.targetSearchType_->GetTypes(); }
    
    void SetFlags(TARGET_FLAGS flags) { base.targetSearchType_->SetFlags(flags); }
    TARGET_FLAGS GetFlags() { return base.targetSearchType_->GetFlags(); }
    
    CTargetSearchType* getTargetType() { return base.targetSearchType_; }
    
    void SetLevel(int level) { level_ = level; }
    int GetLevel() { return level_; }
    
    CAbilityValue* GetMaxTargets() { return base.targetSearchType_->GetMaxTargets(); }
    
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    CAbilityEntity* GetCaster() { return caster_; }

private:
    struct {
        std::string name_;
        long behavior_;
        ABILITY_DAMAGE_TYPE damageType_;  // 伤害类型
        bool isIgnoreSpellImmunity_;      // 是否无视魔免
        unsigned int beginLevel_;   // 初始等级
        unsigned int stepLevel_;    // 每x级升一次
        unsigned int maxLevel_;     // 最大等级
        std::string textureIconName_;   // 图标
        CAbilityValue* castPoint_;  // 施法前摇时间
        CAbilityValue* castWidth_;  // 技能宽度
        CAbilityValue* castRange_;  // 技能释放范围
        CAbilityValue* castRangeBuffer_;    // 释放范围缓冲，当 castRange_ < 目标 < castRangeBuffer_也会自己攻击
        CAbilityValue* aoeRange_;   // 配合ABILITY_BEHAVIOR_AOE使用，显示技能范围
        CAbilityValue* cooldown_;
        CAbilityValue* damage_;     // 伤害
        CAbilityValue* manaCost_;   // 法术消耗
        CAbilityValue* crystalCost_;// 晶石消耗
        CAbilityValue* hpCost_;     // 血量消耗
        // 需要behavier包含 ABILITY_BEHAVIOR_CHANNELLED
        CAbilityValue* channelTime_;    // 持续施法时间
        CAbilityValue* channelledManaCostPerSecond_;    // 持续施法每秒的法术消耗
        CTargetSearchType* targetSearchType_;   // 目标
        
        std::map<EVENT_TYPE, CEvent*> events_;
        SPECIAL_VALUE specials_;
    } base;
    
private:
    int level_;
    double cooldown_;
    float elapsed_;
    bool isValid_;
    CAbilityEntity* caster_;
    std::map<ABILITY_ATTRIBUTE, float> modifyAttributes_;
    std::map<std::string, CModifierData*> modifierData_;
    // 包括选中的、击中的
    CTargetStack* targetStack_;
};

#endif /* CAbility_hpp */
