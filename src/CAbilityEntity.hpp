//
//  CAbilityEntity.hpp
//  SkillLib
//
//  Created by yucong on 2017/8/31.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbilityEntity_hpp
#define CAbilityEntity_hpp

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "SkillTypes.h"
#include "CObject.hpp"
#include "CAbility.hpp"
#include "CAbilityContainer.hpp"
#include "COperate.hpp"
#include "CAbilityEntityData.hpp"

struct ModifierNode {
    std::vector<CModifier*> sameModifiers;
};

class CItem;
class CTargetStack;

class CAbilityEntity : public CObject {
public:
    CAbilityEntity();
    ~CAbilityEntity();
    void Execute();
    void Destroy();
    void Update(float dt);
    
    // 执行指定的技能
    void ExecuteAbility(unsigned index);
    // 执行ability事件
    void ExecuteAbilityEvent(EVENT_TYPE type);
    // 执行modifier事件
    void ExecuteModifierEvent(MODIFIER_EVENT_TYPE type);
    
    void SetTeamId(int teamId) { teamId_ = teamId; }
    int GetTeamId() { return teamId_; }
    
    // attributes
    // ------------------------------------------------------
    void SetEntityAbility(CAbility* ability, unsigned index);
    void SetEntityAbilityLayout(unsigned layout);
    
    
    void SetBaseAttribute(ENTITY_ATTRIBUTES attribute, float value);
    void ModifyAttribute(ENTITY_ATTRIBUTES attribute, float value);
    
    float GetBaseAttribute(ENTITY_ATTRIBUTES attribute);
    float GetModifyAttribute(ENTITY_ATTRIBUTES attribute);
    float GetCurrentAttribute(ENTITY_ATTRIBUTES attribute);
    
    // 等级
    void SetCurrentLevel(int level) { level_ = level; }
    int GetCurrentLevel() { return level_; }
    
    // buff
    void AddModifier(CModifier* modifer);
    void AddModifier(CAbilityEntity* caster, CAbility* ability, std::string modifierName, CTargetStack* stack = NULL);
    const std::map<std::string, ModifierNode*>& GetModifiers();
    void RemoveModifier(CModifier* modifier);
    void RemoveModifier(std::string name);
    void ClearModifier(std::string name);
    bool HasModifier(std::string name);
    
    // item
    void AddItem(CItem* item);
    void RemoveItem(CItem* item);
    bool HasItem(int64_t id);
    
    // type
    ENTITY_TYPE GetType() { return data_->GetType(); }
    
    // properties
    void SetProperties(MODIFIER_PROPERTY property, float value) { properties_[property] = value; }
    void ModifyProperties(MODIFIER_PROPERTY property, float add) {
        if (properties_.find(property) == properties_.end()) properties_[property] = 0.f;
        properties_[property] += add;
    }
    float GetProperties(MODIFIER_PROPERTY property) { return properties_[property]; }
    
    // state
    void SetState(MODIFIER_STATE state, bool b) { states_[state] = b; }
    bool GetState(MODIFIER_STATE state) { return states_[state]; }
    
    // 获取最大值
    float GetHPMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_HP) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_HP_GAIN); }
    float GetManaMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_MANA) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_MANA_GAIN); }
    float GetAttackDamage(int level) {
        float min = this->GetBaseAttribute(ENTITY_ATTRIBUTE_DAMAGE_MIN);
        float max = this->GetBaseAttribute(ENTITY_ATTRIBUTE_DAMAGE_MAX);
        return (rand() % int(max - min + 1)) + min + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_DAMAGE_GAIN);
    }
    float GetArmorMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_ARMOR) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_ARMOR_GAIN); }
    float GetMagicResistMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_MAGIC_RESIST) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_MAGIC_RESIST_GAIN); }
    float GetMoveSpeedMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_MOVE_SPEED) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_MOVE_SPEED_GAIN); }
    float GetStrengthMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_STRENGTH) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_STRENGTH_GAIN); }
    float GetIntelligenceMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_INTELLIGENCE) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_INTELLIGENCE_GAIN); }
    float GetAgilityMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_AGILITY) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_AGILITY_GAIN); }
    float GetPhysicalPenetrateMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE_GAIN); }
    float GetMagicalPenetrateMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_MAGICAL_PENETRATE) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_MAGICAL_PENETRATE_GAIN); }
    
    float GetCurHp() { return GetHPMax(level_) + GetModifyAttribute(ENTITY_ATTRIBUTE_HP_CHANGE); }
    float GetCurMana() { return GetManaMax(level_) + GetModifyAttribute(ENTITY_ATTRIBUTE_MANA_CHANGE); }
    
    float GetCurArmor() {
        return GetArmorMax(level_) + GetModifyAttribute(ENTITY_ATTRIBUTE_ARMOR) + GetProperties(MODIFIER_PROPERTY_PHYSICAL_ARMOR_BONUS); }
    float GetCurMagicResist() {
        return GetMagicResistMax(level_) + GetModifyAttribute(ENTITY_ATTRIBUTE_MAGIC_RESIST) + GetProperties(MODIFIER_PROPERTY_MAGICAL_RESISTANCE_BONUS); }
    float GetCurPhysicalPenetrate() {
        return GetPhysicalPenetrateMax(level_) + GetModifyAttribute(ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE); }
    float GetCurMagicalPenetrate() {
        return GetMagicalPenetrateMax(level_) + GetModifyAttribute(ENTITY_ATTRIBUTE_MAGICAL_PENETRATE); }
    
    //
    void SetAttacker(CAbilityEntity* attacker) { attacker_ = attacker; }
    CAbilityEntity* GetAttacker() { return attacker_; }
    
    CSize GetSize() { return CSize(data_->GetSize()); }
    CVector GetCollisionCenter() { return CVector(position_.GetX(), position_.GetY() + data_->GetSize().height/2); }
    
    void SetPosition(float x, float y) { position_.SetX(x); position_.SetY(y); }
    void SetPositionX(float x) { position_.SetX(x); }
    void SetPositionY(float y) { position_.SetY(y); }
    const CVector& GetPosition() { return position_; }
    
    void SetData(CAbilityEntityData* data);
    CAbilityEntityData* GetData() { return data_; }
    
private:
    // base data
    //----------------------------------------------------------------
    int level_;                         // 单位等级
    CAbilityContainer* abilityContainer_;               // 技能
    CAbilityEntity* attacker_;          // 攻击者
    CAbilityEntityData* data_;

    // 变化的数据
    //----------------------------------------------------------------
    int teamId_;                                        // 队伍id
    CVector position_;                                   // 位置
    std::map<ENTITY_ATTRIBUTES, float> modifyAttributes_;   // 变动属性
    std::map<MODIFIER_PROPERTY, float> properties_;
    std::map<MODIFIER_STATE, bool> states_;
    std::map<std::string, ModifierNode*> modifiers_;
    std::vector<CItem*> items_;
    
    // 边界设置
    //----------------------------------------------------------------
    // "BoundsHullName"            "DOTA_HULL_SIZE_HERO"   // 碰撞边界类型，以下为单位尺寸参数:
    // 值                             Hammer中的单位半径
    // DOTA_HULL_SIZE_SMALL            8
    // DOTA_HULL_SIZE_REGULAR          16
    // DOTA_HULL_SIZE_SIEGE            16
    // DOTA_HULL_SIZE_HERO             24
    // DOTA_HULL_SIZE_HUGE             80
    // DOTA_HULL_SIZE_BUILDING         81
    // DOTA_HULL_SIZE_FILLER           96
    // DOTA_HULL_SIZE_BARRACKS         144
    // DOTA_HULL_SIZE_TOWER            144
    
};

#endif /* CAbilityEntity_hpp */
