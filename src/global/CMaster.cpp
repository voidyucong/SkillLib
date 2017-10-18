//
//  CMaster.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/29.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CMaster.hpp"
#include "CAbilityEntity.hpp"
#include "CAbility.hpp"
#include "SkillTypes.h"
#include "MathUtil.hpp"
#include "CModifier.h"
#include "CAbilityEntityLogManager.hpp"

void CMaster::ApplyDamage(CAbilityEntity* victim,
                          CAbilityEntity* attacker,
                          float damage,
                          ABILITY_DAMAGE_TYPE type,
                          long damgeFlags,
                          CAbility* ability
                          ) {
    float realDamage = damage;
    // 目标是否物理免疫状态
    if (type == ABILITY_DAMAGE_TYPE_PHYSICAL && victim->GetState(MODIFIER_STATE_ATTACK_IMMUNE)) {
        realDamage = 0;
    }
    // 目标是否魔法免疫状态
    if (type == ABILITY_DAMAGE_TYPE_MAGICAL && victim->GetState(MODIFIER_STATE_MAGIC_IMMUNE)) {
        realDamage = 0;
    }
    // 目标是否无敌
    if (victim->GetState(MODIFIER_STATE_INVULNERABLE)) {
        realDamage = 0;
    }
    if (type != ABILITY_DAMAGE_TYPE_PURE) {
        // 物防、免伤、盾计算
        if (type == ABILITY_DAMAGE_TYPE_PHYSICAL) {
            // 扣除免伤固定值
            realDamage -= victim->GetProperties(MODIFIER_PROPERTY_PHYSICAL_ATTACK_RELIEF_BONUS);
            // 计算免伤百分比
            float armor = victim->GetCurArmor() - attacker->GetCurPhysicalPenetrate();
            float relief = armor / (armor + 602);
            relief += victim->GetProperties(MODIFIER_PROPERTY_PHYSICAL_ATTACK_RELIEF_PERCENT_BONUS);
            realDamage *= 1 - relief;
            // 修改护盾
            float shield = victim->GetProperties(MODIFIER_PROPERTY_PHYSICAL_ARMOR_SHIELD_BONUS);
            shield -= realDamage;
            shield = MAX(shield, 0.f);
            victim->ModifyProperties(MODIFIER_PROPERTY_PHYSICAL_ARMOR_SHIELD_BONUS, shield);
            realDamage -= shield;
        }
        // 魔防、免伤、盾计算
        if (type == ABILITY_DAMAGE_TYPE_MAGICAL) {
            realDamage -= victim->GetProperties(MODIFIER_PROPERTY_MAGICAL_ATTACK_RELIEF_BONUS);
            float resist = victim->GetCurMagicResist() - attacker->GetCurMagicalPenetrate();
            float relief = resist / (resist + 602);
            relief += victim->GetProperties(MODIFIER_PROPERTY_MAGICAL_ATTACK_RELIEF_PERCENT_BONUS);
            realDamage *= 1 - relief;
            // 修改护盾
            float shield = victim->GetProperties(MODIFIER_PROPERTY_MAGICAL_ARMOR_SHIELD_BONUS);
            shield -= realDamage;
            shield = MAX(shield, 0.f);
            victim->ModifyProperties(MODIFIER_PROPERTY_MAGICAL_ARMOR_SHIELD_BONUS, shield);
            realDamage -= shield;
        }
    }
    
    // 百分比加/减伤害
    if (type == ABILITY_DAMAGE_TYPE_PHYSICAL) {
        float percent = victim->GetProperties(MODIFIER_PROPERTY_INCOMING_PHYSICAL_DAMAGE_PERCENTAGE);
        realDamage *= 1 + percent;
    }
    if (type == ABILITY_DAMAGE_TYPE_MAGICAL) {
        float percent = victim->GetProperties(MODIFIER_PROPERTY_INCOMING_SPELL_DAMAGE_CONSTANT);
        realDamage *= 1 + percent;
    }
    
    realDamage = MAX(realDamage, 0.f);
    // 受害者保存攻击者信息，方便报仇
    victim->SetAttacker(attacker);
    // 减血
    victim->ModifyAttribute(ENTITY_ATTRIBUTE_CUR_HP, -int(realDamage));
    
    std::cout << "Damage Caster: " << attacker << " Target:" << victim << " Damage:" << damage << " Real:" << realDamage << std::endl;
    
    // 记录log
    CAbilityEntityLogManager::getInstance()->AddFightLog(attacker, victim, int(realDamage), ability);
    
    float curHP = victim->GetCurHp();
    if (curHP <= 0) {
        if (ability) {
            victim->ExecuteAbilityEvent(EVENT_TYPE_ON_DEATH);
            victim->ExecuteModifierEvent(MODIFIER_EVENT_ON_DEATH); // 死亡时
            
            attacker->ExecuteModifierEvent(MODIFIER_EVENT_ON_KILL_HERO);   // 杀死英雄时
        }
    }
    
    // 事件
    attacker->ExecuteModifierEvent(MODIFIER_EVENT_ON_ATTACK_LANDED);  // 攻击到时
    attacker->ExecuteModifierEvent(MODIFIER_EVENT_ON_DEAL_DAMAGE);  // 施加伤害时
    
    victim->ExecuteModifierEvent(MODIFIER_EVENT_ON_ATTACKED);  // 被攻击时
    victim->ExecuteModifierEvent(MODIFIER_EVENT_ON_TAKE_DAMAGE);   // 受到伤害时
    
        
    // 吸血
    // 目前定义只有普通攻击可吸血，技能需要自定义操作COpLifesteal进行处理
    float lifesteal = 0.f;
    if (type == ABILITY_DAMAGE_TYPE_PHYSICAL && !ability) {
        lifesteal = attacker->GetBaseAttribute(ENTITY_ATTRIBUTE_PHYSICAL_LIFESTEAL) *
                    (1 + attacker->GetProperties(MODIFIER_PROPERTY_PHYSICAL_ATTACK_LIFESTEAL_PERCENT_BONUS));
    }
    if (type == ABILITY_DAMAGE_TYPE_MAGICAL && !ability) {
        lifesteal = attacker->GetBaseAttribute(ENTITY_ATTRIBUTE_MAGICAL_LIFESTEAL) *
                    (1 + attacker->GetProperties(MODIFIER_PROPERTY_MAGICAL_ATTACK_LIFESTEAL_PERCENT_BONUS));
    }
    ApplyHealth(attacker, NULL, realDamage * lifesteal);
    
    // 清空攻击者信息
    victim->SetAttacker(NULL);
}

void CMaster::ApplyHealth(CAbilityEntity* target, CAbilityEntity* source, float value) {
    // 死亡后不回血
    
    float realValue = value;
    // 回复加成
    realValue *= 1 + target->GetProperties(MODIFIER_PROPERTY_HEALTH_REGEN_ADDITION_PERCENT);
    if (realValue <= 0) {
        return;
    }
    
    target->ModifyAttribute(ENTITY_ATTRIBUTE_CUR_HP, realValue);
    // 受到治疗
    if (source && source != target) {
        target->ExecuteModifierEvent(MODIFIER_EVENT_ON_HEAL_RECEIVED);
    }
    // 主动获得生命值
    else {
        target->ExecuteModifierEvent(MODIFIER_EVENT_ON_HEALTH_GAINED);
    }
    
    std::cout << "Heal Caster: " << source << " Target:" << target << " Value:" << value << " Real:" << realValue << std::endl;
}
