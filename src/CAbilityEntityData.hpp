//
//  CAbilityEntityData.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbilityEntityData_hpp
#define CAbilityEntityData_hpp

#include <iostream>
#include <map>
#include <vector>
#include "CObject.hpp"
#include "SkillTypes.h"


class CAbilityEntityData {
public:
    CAbilityEntityData() {}
    ~CAbilityEntityData() {}
    
    std::string GetName() { return name_; }
    void SetName(std::string value) { name_ = value; }
    // 基础设置
    //----------------------------------------------------------------
    void SetLevel(int value) { level_ = value; }
    int GetLevel() { return level_; }                 // 单位等级
    void SetModelFile(std::string value) { modelFile_ = value; }
    std::string GetModelFile() { return modelFile_; }   // 模型文件
    void SetModelScale(float value) { modelScale_ = value; }
    float GetModelScale() { return modelScale_; }               // 模型大小，
    void SetMinimapIcon(std::string value) { minimapIcon_ = value; }
    std::string GetMinimapIcon() { return minimapIcon_; }      // 小地图图标
    void SetMinimapIconSize(float value) { minimapIconSize_ = value; }
    float GetMinimapIconSize() { return minimapIconSize_; }                     // 小地图图标尺寸
    void SetIsIsNeutralUnitType(bool value) { isIsNeutralUnitType_ = value; }
    bool GetIsIsNeutralUnitType() { return isIsNeutralUnitType_; }                 // 是否是中立单位，相关Lua函数: IsNeutralUnitType()
    void SetIsAutoAttacksByDefault(bool value) { isAutoAttacksByDefault_ = value; }
    bool GetIsAutoAttacksByDefault() { return isAutoAttacksByDefault_; }                 // 是否自动攻击，0为不自动攻击
    
    // 声音 SoundSet 加上正确的 GameSoundsFile 可以提供攻击和脚步声等音效
    // SoundSet 字符串是每个英雄声音的第一部分，可以在Dota2声音编辑器中查找到
    void SetSoundFile(std::string value) { soundFile_ = value; }
    std::string GetSoundFile() { return soundFile_; }
    void SetGameSoundsFile(std::string value) { gameSoundsFile_ = value; }
    std::string GetGameSoundsFile() { return gameSoundsFile_; }
    
    // 技能设置
    //----------------------------------------------------------------
    void SetAbilityLayout(int value) { abilityLayout_ = value; }
    int GetAbilityLayout() { return abilityLayout_; }          // 技能槽数量，最低4个，最高为6个，单位可以同时拥有最多16个技能
    void SetAbility(std::string name, int idx) { abilities_[idx] = name; }
    std::string GetAbility(int idx) { return abilities_[idx]; }
    
    void SetProjectileModel(std::string value) { projectileModel_ = value; }
    std::string GetProjectileModel() { return projectileModel_; }                          // 投射物，填写特效路径，只有投射物特效才行
    
    
    // 属性设置
    //----------------------------------------------------------------
    void SetType(ENTITY_TYPE value) { type_ = value; }
    ENTITY_TYPE GetType() { return type_; }                                  // 类型 英雄|建筑|野怪
    void SetPrimary(ENTITY_ATTRIBUTE_PRIMARY value) { primary_ = value; }
    ENTITY_ATTRIBUTE_PRIMARY GetPrimary() { return primary_; }                  // 主属性类型
    void SetMovementCapability(ENTITY_MOVEMENT_CAPABILITY value) { movementCapability_ = value; }
    ENTITY_MOVEMENT_CAPABILITY GetMovementCapability() { return movementCapability_; }     // 移动能力 不能移动|地面|飞行
    void SetAttackCapability(ENTITY_ATTACK_CAPABILITY value) { attackCapability_ = value; }
    ENTITY_ATTACK_CAPABILITY GetAttackCapability() { return attackCapability_; }         // 攻击能力 不能攻击|近战|远程
    
    void SetBaseAttributes(ENTITY_ATTRIBUTES attribute, float value) { baseAttributes_[attribute] = value; }
    float GetAttributes(ENTITY_ATTRIBUTES attribute) {
        if (baseAttributes_.find(attribute) != baseAttributes_.end()) {
            return baseAttributes_[attribute];
        }
        return 0.f;
    }
    
    void SetBaseStrength(float value) { baseAttributes_[ENTITY_ATTRIBUTE_STRENGTH] = value; }
    float GetBaseStrength() { return baseAttributes_[ENTITY_ATTRIBUTE_STRENGTH]; }
    void SetStrengthGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_STRENGTH_GAIN] = value; }
    float GetStrengthGain() { return baseAttributes_[ENTITY_ATTRIBUTE_STRENGTH_GAIN]; }
    void SetBaseIntelligence(float value) { baseAttributes_[ENTITY_ATTRIBUTE_INTELLIGENCE] = value; }
    float GetBaseIntelligence() { return baseAttributes_[ENTITY_ATTRIBUTE_INTELLIGENCE]; }
    void SetIntelligenceGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_INTELLIGENCE_GAIN] = value; }
    float GetIntelligenceGain() { return baseAttributes_[ENTITY_ATTRIBUTE_INTELLIGENCE_GAIN]; }
    void SetBaseAgility(float value) { baseAttributes_[ENTITY_ATTRIBUTE_AGILITY] = value; }
    float GetBaseAgility() { return baseAttributes_[ENTITY_ATTRIBUTE_AGILITY]; }
    void SetAgilityGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_AGILITY_GAIN] = value; }
    float GetAgilityGain() { return baseAttributes_[ENTITY_ATTRIBUTE_AGILITY_GAIN]; }
    void SetBaseHP(float value) { baseAttributes_[ENTITY_ATTRIBUTE_HP] = value; }
    float GetBaseHP() { return baseAttributes_[ENTITY_ATTRIBUTE_HP]; }
    void SetHPGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_HP_GAIN] = value; }
    float GetHPGain() { return baseAttributes_[ENTITY_ATTRIBUTE_HP_GAIN]; }
    void SetHPRegen(float value) { baseAttributes_[ENTITY_ATTRIBUTE_HP_REGEN] = value; }
    float GetHPRegen() { return baseAttributes_[ENTITY_ATTRIBUTE_HP_REGEN]; }
    void SetBaseMana(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MANA] = value; }
    float GetBaseMana() { return baseAttributes_[ENTITY_ATTRIBUTE_MANA]; }
    void SetManaGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MANA_GAIN] = value; }
    float GetManaGain() { return baseAttributes_[ENTITY_ATTRIBUTE_MANA_GAIN]; }
    void SetManaRegen(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MANA_REGEN] = value; }
    float GetManaRegen() { return baseAttributes_[ENTITY_ATTRIBUTE_MANA_REGEN]; }
    void SetStartingMana(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MANA_STARTING] = value; }
    float GetStartingMana() { return baseAttributes_[ENTITY_ATTRIBUTE_MANA_STARTING]; }
    void SetDamageGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_DAMAGE_GAIN] = value; }
    float GetDamageGain() { return baseAttributes_[ENTITY_ATTRIBUTE_DAMAGE_GAIN]; }
    void SetArmorPhysical(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ARMOR] = value; }
    float GetArmorPhysical() { return baseAttributes_[ENTITY_ATTRIBUTE_ARMOR]; }
    void SetArmorGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ARMOR_GAIN] = value; }
    float GetArmorGain() { return baseAttributes_[ENTITY_ATTRIBUTE_ARMOR_GAIN]; }
    void SetMagicalResist(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MAGIC_RESIST] = value; }
    float GetMagicalResist() { return baseAttributes_[ENTITY_ATTRIBUTE_MAGIC_RESIST]; }
    void SetMagicResistGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MAGIC_RESIST_GAIN] = value; }
    float GetMagicResistGain() { return baseAttributes_[ENTITY_ATTRIBUTE_MAGIC_RESIST_GAIN]; }
    void SetMovementSpeed(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MOVE_SPEED] = value; }
    float GetMovementSpeed() { return baseAttributes_[ENTITY_ATTRIBUTE_MOVE_SPEED]; }
    void SetMoveSpeedGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MOVE_SPEED_GAIN] = value; }
    float GetMoveSpeedGain() { return baseAttributes_[ENTITY_ATTRIBUTE_MOVE_SPEED_GAIN]; }
    void SetPhysicalLifesteal(float value) { baseAttributes_[ENTITY_ATTRIBUTE_PHYSICAL_LIFESTEAL] = value; }
    float GetPhysicalLifesteal() { return baseAttributes_[ENTITY_ATTRIBUTE_PHYSICAL_LIFESTEAL]; }
    void SetMagicalLifesteal(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MAGICAL_LIFESTEAL] = value; }
    float GetMagicalLifeteal() { return baseAttributes_[ENTITY_ATTRIBUTE_MAGICAL_LIFESTEAL]; }
    void SetBasePhysicalPenetrate(float value) { baseAttributes_[ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE] = value; }
    float GetBasePhysicalPenetrate() { return baseAttributes_[ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE]; }
    void SetPhysicalPenetrateGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE_GAIN] = value; }
    float GetPhysicalPenetrateGain() { return baseAttributes_[ENTITY_ATTRIBUTE_PHYSICAL_PENETRATE_GAIN]; }
    void SetBaseMagicalPenetrate(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MAGICAL_PENETRATE] = value; }
    float GetBaseMagicalPenetrate() { return baseAttributes_[ENTITY_ATTRIBUTE_MAGICAL_PENETRATE]; }
    void SetMagicalPenetrateGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_MAGICAL_PENETRATE_GAIN] = value; }
    float GetMagicalPenetrateGain() { return baseAttributes_[ENTITY_ATTRIBUTE_MAGICAL_PENETRATE_GAIN]; }
    void SetXPGain(float value) { baseAttributes_[ENTITY_ATTRIBUTE_XP_GAIN] = value; }
    float GetXPGain() { return baseAttributes_[ENTITY_ATTRIBUTE_XP_GAIN]; }
    void SetVisionRange(float value) { baseAttributes_[ENTITY_ATTRIBUTE_VISION_RANGE] = value; }
    float GetVisionRange() { return baseAttributes_[ENTITY_ATTRIBUTE_VISION_RANGE]; }
    void SetAttackDamageMin(float value) { baseAttributes_[ENTITY_ATTRIBUTE_DAMAGE_MIN] = value; }
    float GetAttackDamageMin() { return baseAttributes_[ENTITY_ATTRIBUTE_DAMAGE_MIN]; }                       // 最小伤害
    void SetAttackDamageMax(float value) { baseAttributes_[ENTITY_ATTRIBUTE_DAMAGE_MAX] = value; }
    float GetAttackDamageMax() { return baseAttributes_[ENTITY_ATTRIBUTE_DAMAGE_MAX]; }                       // 最大伤害
    void SetAttackRate(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_RATE] = value; }
    float GetAttackRate() { return baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_RATE]; }                       // 攻击间隔
    void SetAttackAnimationPoint(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_POINT] = value; }
    float GetAttackAnimationPoint() { return baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_POINT]; }                      // 攻击前摇
    void SetAttackAcquisitionRange(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_ACQUISITION_RANGE] = value; }
    float GetAttackAcquisitionRange() { return baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_ACQUISITION_RANGE]; }                       // 警戒范围
    void SetAttackRange(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_RANGE] = value; }
    float GetAttackRange() { return baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_RANGE]; }                       // 攻击范围
    void SetAttackRangeBuffer(float value) { baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_RANGE_BUFFER] = value; }
    float GetAttackRangeBuffer() { return baseAttributes_[ENTITY_ATTRIBUTE_ATTACK_RANGE_BUFFER]; }                       // 攻击缓冲范围（不会取消攻击的额外射程范围）
    void SetProjectileSpeed(float value) { baseAttributes_[ENTITY_ATTRIBUTE_PROJECTILE_SPEED] = value; }
    float GetProjectileSpeed() { return baseAttributes_[ENTITY_ATTRIBUTE_PROJECTILE_SPEED]; }                       // 投射速率

    
    void SetSize(CSize value) { size_ = value; }
    CSize GetSize() { return size_; }
    void SetCollisionRadius(float value) { collisionRadius_ = value; }
    float GetCollisionRadius() { return collisionRadius_; }
    void SetHealthBarOffset(int value) { healthBarOffset_ = value; }
    int GetHealthBarOffset() { return healthBarOffset_; }                   // 血条高度，缺省值为 "-1"，意味着使用默认的模型高度
    
    void SetScript(std::string value) { script_ = value; }
    std::string GetScript() { return script_; }
    
private:
    std::string name_;
    // 基础设置
    //----------------------------------------------------------------
    int level_;                 // 单位等级
    std::string modelFile_;   // 模型文件
    float modelScale_;               // 模型大小，
    std::string minimapIcon_;      // 小地图图标
    float minimapIconSize_;                     // 小地图图标尺寸
    bool isIsNeutralUnitType_;                 // 是否是中立单位，相关Lua函数: IsNeutralUnitType()
    bool isAutoAttacksByDefault_;                 // 是否自动攻击，0为不自动攻击
    
    // 声音 SoundSet 加上正确的 GameSoundsFile 可以提供攻击和脚步声等音效
    std::string soundFile_;
    std::string gameSoundsFile_;
    
    int abilityLayout_;          // 技能槽数量，最低4个，最高为6个，单位可以同时拥有最多16个技能
    std::map<int, std::string> abilities_;
    std::string projectileModel_;                          // 投射物，填写特效路径，只有投射物特效才行
    
    
    // 属性设置
    //----------------------------------------------------------------
    ENTITY_TYPE type_;                                  // 类型 英雄|建筑|野怪
    ENTITY_ATTRIBUTE_PRIMARY primary_;                  // 主属性类型
    ENTITY_MOVEMENT_CAPABILITY movementCapability_;     // 移动能力 不能移动|地面|飞行
    ENTITY_ATTACK_CAPABILITY attackCapability_;         // 攻击能力 不能攻击|近战|远程
    
    std::map<ENTITY_ATTRIBUTES, float> baseAttributes_;     // 所有基础属性
    
    CSize size_;
    float collisionRadius_;
    int healthBarOffset_;                   // 血条高度，缺省值为 "-1"，意味着使用默认的模型高度
    
    std::string script_;
};

#endif /* CAbilityEntityData_hpp */
