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
#include <map>
#include "SkillTypes.h"
#include "CObject.hpp"
#include "CAbility.hpp"
#include "CAbilityContainer.hpp"
#include "COperate.hpp"

//class CAbilityContainer;
//class CAbility;

struct ModifierNode {
    std::vector<CModifier*> sameModifiers;
};

class CAbilityEntity : public CObject {
public:
    CAbilityEntity();
    ~CAbilityEntity();
    void Execute();
    void Destroy();
    void Update(float dt);
    
    // 执行指定的技能
    void ExecuteAbility(unsigned index);
    
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
    void AddModifer(CModifier* modifer);
    void RemoveModifier(CModifier* modifier);
    void ClearModifier(std::string name);
    
    // type
    void SetType(ENTITY_TYPE type) { type_ = type; }
    ENTITY_TYPE GetType() { return type_; }
    
    // 获取最大值
    float GetHPMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_HP) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_HP_GAIN); }
    float GetManaMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_MANA) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_MANA_GAIN); }
    float GetDamageMax(int level) {
        return this->GetBaseAttribute(ENTITY_ATTRIBUTE_DAMAGE) + (level - 1) * this->GetBaseAttribute(ENTITY_ATTRIBUTE_DAMAGE_GAIN); }
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
    
private:
    // base data
    //----------------------------------------------------------------
    int level_;                         // 单位等级
    std::string modelName_;             // 模型文件
    float modelScale_;                  // 模型缩放大小，
    std::string minimapIconName_;       // 小地图图标
    float minimapIconSize_;             // 小地图图标尺寸
    std::string tag_;                   // 单位标签，可以是任何名字字符，使用Lua代码GetUnitLabel()可以获取到这里的键值
    bool isNeutralUnitType_;            // 是否是中立单位，相关Lua函数: IsNeutralUnitType()
    bool isAutoAttacks_;                // 是否自动攻击，0为不自动攻击
    
    float healthBarOffset_;                             // 血条高度，缺省值为 "-1"，意味着使用默认的模型高度
    std::string vscript_;                               // 这会在单位诞生后立即装载一个脚本文件,使用诞生函数 ( entityKeyValues ) 可以启动一个计时器来进行任何操作
    std::string projectileModelName_;                   // 抛射物模型
    
    CAbilityContainer* abilityContainer_;               // 技能
    
    ENTITY_TYPE type_;                                  // 类型 英雄|建筑|野怪
    ENTITY_ATTRIBUTE_PRIMARY primary_;                  // 主属性类型
    ENTITY_MOVEMENT_CAPABILITY movementCapability_;     // 移动能力 不能移动|地面|飞行
    ENTITY_ATTACK_CAPABILITY attackCapability_;         // 攻击能力 不能攻击|近战|远程
    
    std::map<ENTITY_ATTRIBUTES, float> baseAttributes_;     // 所有基础属性

    // 变化的数据
    //----------------------------------------------------------------
    int teamId_;                                        // 队伍id
    std::map<ENTITY_ATTRIBUTES, float> modifyAttributes_;   // 变动属性
    std::map<std::string, ModifierNode*> buffs_;
    std::map<std::string, ModifierNode*> debuffs_;
    
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
