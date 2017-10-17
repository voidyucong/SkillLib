//
//  SkillReaderJson.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/12.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "SkillReaderJson.hpp"
#include "CAbility.hpp"
#include "CAbilityValue.hpp"
#include "CEvent.hpp"
#include "CModifierEvent.hpp"
#include "CModifierData.hpp"
#include "COperate.hpp"
#include "SkillTypesMapping.h"
#include "CLinearProjectile.hpp"
#include "CTrackingProjectile.hpp"
#include "CRunScript.hpp"

using namespace SKB;
#define RUTL ReaderJsonUtil

static SkillReaderJson* s_pInstance = NULL;

SkillReaderJson::SkillReaderJson() {
    
}

SkillReaderJson::~SkillReaderJson() {
    
}

SkillReaderJson* SkillReaderJson::getInstance() {
    if (!s_pInstance) {
        s_pInstance = new SkillReaderJson();
    }
    return s_pInstance;
}

CAbility* SkillReaderJson::AbilityFromFile(std::string fileName) {
    rapidjson::Document json;
    FILE* f = fopen(fileName.c_str(), "r+");
    assert(f);
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    char* pBuf = (char*)malloc(len + 1);
    rewind(f);
    fread(pBuf, 1, len, f);
    pBuf[len] = 0;
    fclose(f);
    
    json.Parse<0>(pBuf);
    if (json.HasParseError())
    {
        std::cout << "GetParseError " << json.GetParseError() << std::endl;
        return NULL;
    }
    
    CAbility* ability = CreateAbility(json);
    
    free((void*)pBuf);

    return ability;
}


CAbility* SkillReaderJson::CreateAbility(const rapidjson::Value& json) {
    if (json.IsNull()) return NULL;
    
    CAbility* ability = new CAbility();
    // special value
    ParseSpecialValue(json["AbilitySpecial"], ability);
    
    // name
    ability->SetName(RUTL::GetJsonStringValueFromDic(json, "name"));
    // AbilityBehavior
    long behavior = 0;
    for (int i = 0; i < RUTL::GetJsonArraySize(json["AbilityBehavior"]); ++i) {
        std::string behaviorstr = RUTL::GetJsonStringValueFromArray(json["AbilityBehavior"], i);
        behavior |= SKB::GetEnumByString(behaviorstr);
    }
    ability->SetBehavior(behavior);
    // target
    if (behavior & ABILITY_BEHAVIOR_UNIT_TARGET) {
        assert(RUTL::CheckJsonIsKeyNotNull(json, "AbilityUnitTargetTeam"));
        // team
        ability->getTargetType()->SetTeams((TARGET_TEAMS)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AbilityUnitTargetTeam", "TARGET_TEAM_NONE")));
        // type
        ability->getTargetType()->SetTypes((TARGET_TYPES)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AbilityUnitTargetType", "TARGET_TYPE_ALL")));
        // flags
        ability->getTargetType()->SetFlags((TARGET_FLAGS)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AbilityUnitTargetFlags", "TARGET_FLAG_NONE")));
        // center
        ability->getTargetType()->SetCenter(TARGET_CENTER_CASTER);
        // radius
        ability->getTargetType()->SetRadius(RUTL::CheckJsonIsKeyNotNull(json, "AbilityCastRange") ? RUTL::CreateVariableList<float>(json, "AbilityCastRange", ability) : NULL);
        // max targets
        ability->getTargetType()->SetMaxTargets(RUTL::CheckJsonIsKeyNotNull(json, "AbilityMaxTargets") ? RUTL::CreateVariableList<float>(json, "AbilityMaxTargets", ability) : NULL);
    }
    // damage type
    ability->SetDamageType((ABILITY_DAMAGE_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AbilityUnitDamageType")));
    // ignore spell immunity
    ability->SetIsIgnoreSpellImmunity(RUTL::GetJsonBooleanValueFromDic(json, "IsIgnoreSpellImmunity"));
    // begin level
    ability->SetBeginLevel(RUTL::GetJsonIntValueFromDic(json, "BeginLevel", 1));
    // step level
    ability->SetBeginLevel(RUTL::GetJsonIntValueFromDic(json, "StepLevel", 1));
    // max level
    ability->SetMaxLevel(RUTL::GetJsonIntValueFromDic(json, "MaxLevel", 1));
    // texture name
    ability->SetTextureIconName(RUTL::GetJsonStringValueFromDic(json, "AbilityTextureName"));
    // cast width
    ability->SetCastWidth(RUTL::CreateVariableList<float>(json, "AbilityCastWidth", ability));
    // cast range
    ability->SetCastRange(RUTL::CheckJsonIsKeyNotNull(json, "AbilityCastRange") ? RUTL::CreateVariableList<float>(json, "AbilityCastRange", ability) : NULL);
    // cast point
    ability->SetCastPoint(RUTL::CreateVariableList<float>(json, "AbilityCastPoint", ability));
    if (behavior & ABILITY_BEHAVIOR_AOE) {
        // aoe range
        ability->SetAoeRange(RUTL::CreateVariableList<float>(json, "AoeRadius", ability));
    }
    // cooldown
    ability->SetBaseCooldown(RUTL::CreateVariableList<float>(json, "AbilityCooldown", ability));
    // mana cost
    ability->SetManaCost(RUTL::CreateVariableList<float>(json, "AbilityManaCost", ability));
    // damage
    ability->SetDamage(RUTL::CreateVariableList<float>(json, "AbilityDamage", ability));
    
    // Event
    ParseAbilityEvent(json, ability);
    
    // Modifiers
    ParseModifiers(json, ability);
    
    return ability;
}

void SkillReaderJson::ParseSpecialValue(const rapidjson::Value& json, CAbility* ability) {
    if (json.IsNull()) return;
    for (int i = 0; i < RUTL::GetJsonArraySize(json); ++i) {
        const rapidjson::Value& item = json[i];
        if (item.IsNull()) continue;
        CAbilityValue* value = RUTL::CreateVariableList2(item, "value", RUTL::GetJsonStringValueFromDic(item, "type"), ability);
        ability->AddSpecialValue(value, RUTL::GetJsonStringValueFromDic(item, "key"));
    }
}

void SkillReaderJson::ParseAbilityEvent(const rapidjson::Value& json, CAbility* ability) {
    std::map<EVENT_TYPE, std::string> events = {
        {EVENT_TYPE_ON_SPELL_START, "OnSpellStart"},
        {EVENT_TYPE_ON_TOGGLE_ON, "OnToggleOn"},                    // 当切换为开启状态
        {EVENT_TYPE_ON_TOGGLE_OFF, "OnToggleOff"},                  // 当切换为关闭状态
        {EVENT_TYPE_ON_CHANNEL_FINISH, "OnChannelFinish"},          // 当持续性施法完成
        {EVENT_TYPE_ON_CHANNEL_INTERRUPTED, "OnChannelInterrupted"},// 当持续性施法被中断
        {EVENT_TYPE_ON_CHANNEL_SUCCESS, "OnChannelSuccess"},		// 当持续性施法成功
        {EVENT_TYPE_ON_DEATH, "OnDeath"},                           // 当拥有者死亡
        {EVENT_TYPE_ON_SPAWNED, "OnSpawned"},                       // 当拥有者出生
        {EVENT_TYPE_ON_PROJECTILE_HIT, "OnProjectileHit"},          // 当弹道粒子特效命中单位
        {EVENT_TYPE_ON_PROJECTILE_FINISH, "OnProjectileFinish"},	// 当弹道粒子特效结束
    };
    
    for (auto iter = events.begin(); iter != events.end(); ++iter) {
        CEvent* event = CreateAbilityEvent(json, iter->second, ability);
        if (event) {
            ability->SetEvent(iter->first, event);
        }
    }
}

CEvent* SkillReaderJson::CreateAbilityEvent(const rapidjson::Value& json, std::string eventName, CAbility* ability) {
    if (json.IsNull() || !RUTL::CheckJsonIsKeyNotNull(json, eventName.c_str())) return NULL;
    const rapidjson::Value& eventdata = json[eventName.c_str()];
    CEvent* event = new CEvent();
    ParseOperate(eventdata, event, ability);
    return event;
}

void SkillReaderJson::ParseModifierEvent(const rapidjson::Value& json, CModifierData* modifier, CAbility* ability) {
    std::map<MODIFIER_EVENT_TYPE, std::string> events = {
        {MODIFIER_EVENT_ON_CREATED, "OnCreated"},                   // 创建时
        {MODIFIER_EVENT_ON_DESTROY, "OnDestroy"},                   // 销毁时
        {MODIFIER_EVENT_ON_ATTACK, "OnAttack"},                     // 攻击时
        {MODIFIER_EVENT_ON_ATTACKED, "OnAttacked"},                 // 被攻击时
        {MODIFIER_EVENT_ON_ATTACK_LANDED, "OnAttackLanded"},        // 攻击到时
        {MODIFIER_EVENT_ON_ATTACK_FAILED, "OnAttackFailed"},        // 攻击单位丢失时
        {MODIFIER_EVENT_ON_ATTACK_ALLIED, "OnAttackAllied"},        // 攻击同盟时
        {MODIFIER_EVENT_ON_DEAL_DAMAGE, "OnDealDamage"},            // 施加伤害时
        {MODIFIER_EVENT_ON_TAKE_DAMAGE, "OnTakeDamage"},            // 收到伤害时
        {MODIFIER_EVENT_ON_DEATH, "OnDeath"},                       // 死亡时
        {MODIFIER_EVENT_ON_KILL, "OnKill"},                         // 杀死任意单位时
        {MODIFIER_EVENT_ON_KILL_HERO, "OnHeroKilled"},              // 杀死英雄时
        {MODIFIER_EVENT_ON_RESPAWN, "OnRespawn"},                   // 重生时
        {MODIFIER_EVENT_ON_ORB, "Orb"},                             // 创建法球
        {MODIFIER_EVENT_ON_ORB_FIRE, "OnOrbFire"},                  // 法球发射时
        {MODIFIER_EVENT_ON_ORB_IMPACT, "OnOrbImpact"},              // 法球命中目标时
        {MODIFIER_EVENT_ON_ABILITY_START, "OnAbilityStart"},        // 施法开始时
        {MODIFIER_EVENT_ON_ABILITY_EXECUTED, "OnAbilityExecuted"},  // 施法结束时
        {MODIFIER_EVENT_ON_HEAL_RECEIVED, "OnHealReceived"},        // 受到治疗时
        {MODIFIER_EVENT_ON_HEALTH_GAINED, "OnHealthGained"},        // 主动获得生命值时
        {MODIFIER_EVENT_ON_MANA_GAINED, "OnManaGained"},            // 主动获得魔法值时
        {MODIFIER_EVENT_ON_MANA_SPENT, "OnManaSpent"},              // 消耗魔法值时
        {MODIFIER_EVENT_ON_ENTITY_MOVED, "OnEntityMoved"},          // 移动时
        {MODIFIER_EVENT_ON_TELEPORTED, "OnTeleported"},             // 传送结束时
        {MODIFIER_EVENT_ON_TELEPORTING, "OnTeleporting"},           // 传送开始时
        {MODIFIER_EVENT_ON_PROJECTILE_DODGE, "OnProjectileDodge"},  // 躲避投射物时
        {MODIFIER_EVENT_ON_INTERVAL, "OnIntervalThink"},            // 定时器

    };
    for (auto iter = events.begin(); iter != events.end(); ++iter) {
        CModifierEvent* event = CreateModifierEvnt(json, iter->second, ability);
        if (event) {
            modifier->SetModifierEvent(iter->first, event);
        }
    }
}

CModifierEvent* SkillReaderJson::CreateModifierEvnt(const rapidjson::Value& json, std::string eventName, CAbility* ability) {
    if (json.IsNull() || !RUTL::CheckJsonIsKeyNotNull(json, eventName.c_str())) return NULL;
    const rapidjson::Value& eventdata = json[eventName.c_str()];
    CModifierEvent* event = new CModifierEvent();
    ParseOperate(eventdata, event, ability);
    return event;
}

void SkillReaderJson::ParseOperate(const rapidjson::Value& json, CEvent* event, CAbility* ability) {
    if (json.IsNull()) return;
    for (auto iter = json.MemberBegin(); iter != json.MemberEnd(); ++iter) {
        if (iter->name == "ApplyModifier") {
            const rapidjson::Value& item = iter->value;
            assert(RUTL::CheckJsonIsKeyNotNull(item, "ModifierName"));
            COpApplyModifier* operate = new COpApplyModifier(RUTL::GetJsonStringValueFromDic(item, "ModifierName"));
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else if (iter->name == "Heal") {
            const rapidjson::Value& item = iter->value;
            assert(RUTL::CheckJsonIsKeyNotNull(item, "HealAmount"));
            COpHeal* operate = new COpHeal(RUTL::CreateVariableList<float>(item, "HealAmount", ability));
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else if (iter->name == "Damage") {
            const rapidjson::Value& item = iter->value;
            assert(RUTL::CheckJsonIsKeyNotNull(item, "Damage"));
            assert(RUTL::CheckJsonIsKeyNotNull(item, "DamageType"));
            COpDamage* operate = new COpDamage();
            operate->SetDamageType((ABILITY_DAMAGE_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(item, "DamageType", "ABILITY_DAMAGE_TYPE_MAGICAL")));
            operate->SetDamage(RUTL::CreateVariableList<float>(item, "Damage", ability));
            if (RUTL::CheckJsonIsKeyNotNull(item, "CurrentHealthPercentBasedDamage"))
                operate->SetCurrentPercent(RUTL::CreateVariableList<float>(item, "CurrentHealthPercentBasedDamage", ability));
            if (RUTL::CheckJsonIsKeyNotNull(item, "MaxHealthPercentBasedDamage"))
                operate->SetMaxPercent(RUTL::CreateVariableList<float>(item, "MaxHealthPercentBasedDamage", ability));
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else if (iter->name == "Log") {
            const rapidjson::Value& item = iter->value;
            COpLog* operate = new COpLog(RUTL::GetJsonStringValueFromDic(item, "text"));
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else if (iter->name == "LinearProjectile") {
            const rapidjson::Value& item = iter->value;
            COpLinearProjectile* operate = new COpLinearProjectile();
            operate->GetData()->SetEffectName(RUTL::GetJsonStringValueFromDic(item, "EffectName", ""));
            operate->GetData()->SetMoveSpeed(RUTL::CreateVariableList<float>(item, "MoveSpeed", ability));
            operate->GetData()->SetStartRadius(RUTL::CreateVariableList<float>(item, "StartRadius", ability));
            operate->GetData()->SetEndRadius(RUTL::CreateVariableList<float>(item, "EndRadius", ability));
            operate->GetData()->SetAttachType((MODIFIER_EFFECT_ATTACH_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(item, "AttachType", "MODIFIER_EFFECT_ATTACH_TYPE_ORIGIN")));
            operate->GetData()->SetIsDeleteOnHit(RUTL::GetJsonBooleanValueFromDic(item, "IsDeleteOnHit", true));
            operate->GetData()->SetLength(RUTL::CreateVariableList<float>(item, "Length", ability));
            operate->GetData()->SetCastRadius(RUTL::CreateVariableList<float>(item, "CastRadius", ability));
            operate->GetData()->SetIsProvidesVision(RUTL::GetJsonBooleanValueFromDic(item, "IsProvidesVision", false));
            if (operate->GetData()->GetIsProvidesVision())
                operate->GetData()->SetVisionRadius(RUTL::CreateVariableList<float>(item, "VisionRadius", ability));
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else if (iter->name == "TrackingProjectile") {
            const rapidjson::Value& item = iter->value;
            COpTrackingProjectile* operate = new COpTrackingProjectile();
            operate->GetData()->SetEffectName(RUTL::GetJsonStringValueFromDic(item, "EffectName", ""));
            operate->GetData()->SetMoveSpeed(RUTL::CreateVariableList<float>(item, "MoveSpeed", ability));
            operate->GetData()->SetAttachType((MODIFIER_EFFECT_ATTACH_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(item, "AttachType", "MODIFIER_EFFECT_ATTACH_TYPE_ORIGIN")));
            operate->GetData()->SetCastRadius(RUTL::CreateVariableList<float>(item, "CastRadius", ability));
            operate->GetData()->SetIsProvidesVision(RUTL::GetJsonBooleanValueFromDic(item, "IsProvidesVision", false));
            operate->GetData()->SetCollisionSize(CSize(RUTL::GetJsonFloatValueFromDic(item, "Width", 0.f),
                                                       RUTL::GetJsonFloatValueFromDic(item, "Height", 0.f)));
            if (operate->GetData()->GetIsProvidesVision())
                operate->GetData()->SetVisionRadius(RUTL::CreateVariableList<float>(item, "VisionRadius", ability));
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else if (iter->name == "RunScript") {
            const rapidjson::Value& item = iter->value;
            COpRunScript* operate = new COpRunScript();
            CRunScript* script = new CRunScript();
            script->SetScript(RUTL::GetJsonStringValueFromDic(item, "ScriptFile"), RUTL::GetJsonStringValueFromDic(item, "Function"));
            for (auto iter = item.MemberBegin(); iter != item.MemberEnd(); ++iter) {
                if (iter->name != "ScriptFile" && iter->name != "Function") {
                    if (iter->value.IsString())
                        script->SetParam(iter->name.GetString(), RUTL::CreateVariableList<std::string>(item, iter->name.GetString(), ability));
                    else if (iter->value.IsFloat() || iter->value.IsInt())
                        script->SetParam(iter->name.GetString(), RUTL::CreateVariableList<float>(item, iter->name.GetString(), ability));
                }
            }
            operate->SetScript(script);
            operate->SetSearchType(ParseTarget(item, ability));
            if (operate) event->AddOperate(operate);
        }
        else {
            std::cout << "Unknow operate name:[" << iter->name.GetString() << "]" << std::endl;
        }
    }
    
}

CTargetSearchType* SkillReaderJson::ParseTarget(const rapidjson::Value& json, CAbility* ability) {
    CTargetSearchType* type = new CTargetSearchType();
    if (json.IsNull() || !RUTL::CheckJsonIsKeyNotNull(json, "Target")) return type;
    // 范围搜索
    if (json["Target"].IsObject()) {
        std::string center = RUTL::GetJsonStringValueFromDic(json, "Center");
        if (center == "TARGET") type->SetCenter(TARGET_CENTER_TARGET);
        else if (center == "CASTER" ) type->SetCenter(TARGET_CENTER_CASTER);
        else if (center == "ATTACKER" ) type->SetCenter(TARGET_CENTER_ATTACKER);
        else if (center == "POINT" ) type->SetCenter(TARGET_CENTER_POINT);
        else if (center == "PROJECTILE" ) type->SetCenter(TARGET_CENTER_PROJECTILE);
        
        std::string team_str = RUTL::GetJsonStringValueFromDic(json["Target"], "Teams", "TARGET_TEAM_NONE");
        type->SetTeams((TARGET_TEAMS)SKB::GetEnumByString(team_str));
        
        std::string type_str = RUTL::GetJsonStringValueFromDic(json["Target"], "Types", "TARGET_TYPE_NONE");
        type->SetTypes((TARGET_TYPES)SKB::GetEnumByString(type_str));
        
        if (RUTL::CheckJsonIsKeyNotNull(json["Target"], "Radius"))
            type->SetRadius(RUTL::CreateVariableList<float>(json["Target"], "Radius", ability));
        
        // max targets
        type->SetMaxTargets(RUTL::CheckJsonIsKeyNotNull(json, "MaxTargets") ? RUTL::CreateVariableList<float>(json, "MaxTargets", ability) : NULL);
    }
    // 已存在
    else {
        std::string target = RUTL::GetJsonStringValueFromDic(json, "Target");
        if (target == "TARGET") type->SetSingle(TARGET_CENTER_TARGET);
        else if (target == "CASTER" ) type->SetSingle(TARGET_CENTER_CASTER);
        else if (target == "ATTACKER" ) type->SetSingle(TARGET_CENTER_ATTACKER);
        type->SetRadius(0);
    }
    return type;
}

void SkillReaderJson::ParseModifiers(const rapidjson::Value& json, CAbility* ability) {
    if (!RUTL::CheckJsonIsKeyNotNull(json, "Modifiers")) return;
    const rapidjson::Value& item = json["Modifiers"];
    for (auto iter = item.MemberBegin(); iter != item.MemberEnd(); ++iter) {
        std::string modifierName = iter->name.GetString();
        CModifierData* modifier = CreateModifier(item, modifierName, ability);
        ability->SetModifierData(modifierName, modifier);
    }
}

CModifierData* SkillReaderJson::CreateModifier(const rapidjson::Value& json, std::string name, CAbility* ability) {
    if (json.IsNull() || json[name.c_str()].IsNull()) return NULL;
    const rapidjson::Value& item = json[name.c_str()];
    CModifierData* modifier = new CModifierData();
    modifier->SetName(name);
    modifier->SetIsBuff(RUTL::GetJsonBooleanValueFromDic(item, "IsBuff"));
    modifier->SetIsDebuff(RUTL::GetJsonBooleanValueFromDic(item, "IsDeBuff"));
    modifier->SetIsPurgable(RUTL::GetJsonBooleanValueFromDic(item, "IsPurgable"));
    modifier->SetIsPassive(RUTL::GetJsonBooleanValueFromDic(item, "IsPassive"));
    modifier->SetIsHidden(RUTL::GetJsonBooleanValueFromDic(item, "IsHidden"));
    modifier->SetDuration(RUTL::CreateVariableList<float>(item, "Duration", ability));
    modifier->SetThinkInterval(RUTL::GetJsonFloatValueFromDic(item, "ThinkInterval"));
    modifier->SetIsMulti(RUTL::GetJsonBooleanValueFromDic(item, "IsMulti"));
    modifier->SetMaxMulti(RUTL::GetJsonIntValueFromDic(item, "MaxMulti", 1));
    modifier->SetTextureName(RUTL::GetJsonStringValueFromDic(item, "TextureName"));
    modifier->SetEffectName(RUTL::GetJsonStringValueFromDic(item, "EffectName"));
    modifier->SetModelName(RUTL::GetJsonStringValueFromDic(item, "ModelName"));
    modifier->SetAttachType((MODIFIER_EFFECT_ATTACH_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(item, "AttachType", "MODIFIER_EFFECT_ATTACH_TYPE_ORIGIN")));
    // aura
    modifier->SetAura(RUTL::GetJsonStringValueFromDic(item, "Aura"));
    modifier->SetAuraRadius(RUTL::CreateVariableList<float>(item, "AuraRadius", ability));
    modifier->SetAuraTargetType(ParseTarget(item, ability));
    // events
    ParseModifierEvent(item, modifier, ability);
    // properties
    if (RUTL::CheckJsonIsKeyNotNull(item, "Properties")) {
        const rapidjson::Value& itemProperty = item["Properties"];
        for (auto iter = itemProperty.MemberBegin(); iter != itemProperty.MemberEnd(); ++iter) {
            std::string name = iter->name.GetString();
            MODIFIER_PROPERTY property = (MODIFIER_PROPERTY)SKB::GetEnumByString(name);
            
            float value = RUTL::GetJsonFloatValueFromDic(iter->value, "Value");
            bool unique = RUTL::GetJsonBooleanValueFromDic(iter->value, "Unique");
            modifier->SetProperty(property, value, unique);
        }
    }
    // states
    if (RUTL::CheckJsonIsKeyNotNull(item, "States")) {
        const rapidjson::Value& itemStates = item["States"];
        for (auto iter = itemStates.MemberBegin(); iter != itemStates.MemberEnd(); ++iter) {
            std::string name = iter->name.GetString();
            MODIFIER_STATE state = (MODIFIER_STATE)SKB::GetEnumByString(name);
            bool value = iter->value.GetBool();
            modifier->SetStates(state, value);
        }
    }
    return modifier;
}
