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

bool CheckJsonIsKeyValid(const rapidjson::Value& json, const char* key) {
    if (json.IsNull()) return false;
    if (json.FindMember(key) == json.MemberEnd()) return false;
    return true;
}

bool CheckJsonIsKeyNotNull(const rapidjson::Value& json, const char* key) {
    if (!CheckJsonIsKeyValid(json, key)) return false;
    if (json[key].IsNull()) return false;
    return true;
}

std::string GetJsonStringValueFromDic(const rapidjson::Value& json, const char* key, std::string def = "") {
    if (!CheckJsonIsKeyNotNull(json, key)) return def;
    return json[key].GetString();
}

float GetJsonFloatValueFromDic(const rapidjson::Value& json, const char* key, float def = 0.f) {
    if (!CheckJsonIsKeyNotNull(json, key)) return def;
    return json[key].GetFloat();
}

int GetJsonIntValueFromDic(const rapidjson::Value& json, const char* key, int def = 0) {
    if (!CheckJsonIsKeyNotNull(json, key)) return def;
    return json[key].GetInt();
}

bool GetJsonBooleanValueFromDic(const rapidjson::Value& json, const char* key, bool def = false) {
    if (!CheckJsonIsKeyNotNull(json, key)) return def;
    return json[key].GetBool();
}

std::string GetJsonStringValueFromArray(const rapidjson::Value& json, int idx, std::string def = "") {
    if (json.IsNull()) return def;
    if (json[idx].IsNull()) return def;
    return json[idx].GetString();
}

float GetJsonFloatValueFromArray(const rapidjson::Value& json, int idx, float def = 0.f) {
    if (json.IsNull()) return def;
    if (json[idx].IsNull()) return def;
    return json[idx].GetFloat();
}

int GetJsonIntValueFromArray(const rapidjson::Value& json, int idx, int def = 0) {
    if (json.IsNull()) return NULL;
    if (json[idx].IsNull()) return def;
    return json[idx].GetInt();
}

bool GetJsonBooleanValueFromArray(const rapidjson::Value& json, int idx, bool def = false) {
    if (json.IsNull()) return NULL;
    if (json[idx].IsNull()) return def;
    return json[idx].GetBool();
}

int GetJsonArraySize(const rapidjson::Value& json) {
    if (json.IsNull()) return NULL;
    return json.Size();
}

int GetJsonDicSize(const rapidjson::Value& json) {
    if (json.IsNull()) return NULL;
    return json.Size();
}

bool GetJsonBooleanValueFromArray(const rapidjson::Value& json, int idx) {
    if (json.IsNull()) return NULL;
    if (json[idx].IsNull()) return NULL;
    return json[idx].GetBool();
}

bool IsJsonReference(std::string name) {
    if (name == "") return false;
    return *(name.begin()) == '%';
}


CAbility* SkillReaderJson::CreateAbility(const rapidjson::Value& json) {
    if (json.IsNull()) return NULL;
    
    CAbility* ability = new CAbility();
    // special value
    ParseSpecialValue(json["AbilitySpecial"], ability);
    
    // name
    ability->SetName(GetJsonStringValueFromDic(json, "name"));
    // AbilityBehavior
    long behavior = 0;
    for (int i = 0; i < GetJsonArraySize(json["AbilityBehavior"]); ++i) {
        std::string behaviorstr = GetJsonStringValueFromArray(json["AbilityBehavior"], i);
        behavior |= SKB::GetEnumByString(behaviorstr);
    }
    ability->SetBehavior(behavior);
    // target
    if (behavior & ABILITY_BEHAVIOR_UNIT_TARGET) {
        assert(CheckJsonIsKeyNotNull(json, "AbilityUnitTargetTeam"));
        // team
        ability->SetTeams((TARGET_TEAMS)SKB::GetEnumByString(GetJsonStringValueFromDic(json, "AbilityUnitTargetTeam", "TARGET_TEAM_NONE")));
        // type
        ability->SetTypes((TARGET_TYPES)SKB::GetEnumByString(GetJsonStringValueFromDic(json, "AbilityUnitTargetType", "TARGET_TYPE_ALL")));
        // flags
        ability->SetFlags((TARGET_FLAGS)SKB::GetEnumByString(GetJsonStringValueFromDic(json, "AbilityUnitTargetFlags", "TARGET_FLAG_NONE")));
        // center
        ability->SetCenter(TARGET_CENTER_CASTER);
        // radius
        ability->SetRadius(CheckJsonIsKeyNotNull(json, "AbilityCastRange") ? CreateVariableList(json["AbilityCastRange"], "float", ability) : NULL);
        // max targets
        ability->SetRadius(CheckJsonIsKeyNotNull(json, "MaxTargets") ? CreateVariableList(json["MaxTargets"], "float", ability) : NULL);
    }
    // damage type
    ability->SetDamageType((ABILITY_DAMAGE_TYPE)SKB::GetEnumByString(GetJsonStringValueFromDic(json, "AbilityUnitDamageType")));
    // ignore spell immunity
    ability->SetIsIgnoreSpellImmunity(GetJsonBooleanValueFromDic(json, "IsIgnoreSpellImmunity"));
    // begin level
    ability->SetBeginLevel(GetJsonIntValueFromDic(json, "BeginLevel", 1));
    // step level
    ability->SetBeginLevel(GetJsonIntValueFromDic(json, "StepLevel", 1));
    // max level
    ability->SetMaxLevel(GetJsonIntValueFromDic(json, "MaxLevel", 1));
    // texture name
    ability->SetTextureIconName(GetJsonStringValueFromDic(json, "AbilityTextureName"));
    // cast width
    ability->SetCastWidth(CreateVariableList(json["AbilityCastWidth"], "float", ability));
    // cast range
    ability->SetCastRange(CheckJsonIsKeyNotNull(json, "AbilityCastRange") ? CreateVariableList(json["AbilityCastRange"], "float", ability) : NULL);
    // cast point
    ability->SetCastPoint(CreateVariableList(json["AbilityCastPoint"], "float", ability));
    // cooldown
    ability->SetBaseCooldown(CreateVariableList(json["AbilityCooldown"], "float", ability));
    // mana cost
    ability->SetManaCost(CreateVariableList(json["AbilityManaCost"], "float", ability));
    // damage
    ability->SetDamage(CreateVariableList(json["AbilityDamage"], "float", ability));
    
    // Event
    ParseAbilityEvent(json, ability);
    
    // Modifiers
    ParseModifiers(json, ability);
    
    return ability;
}

void SkillReaderJson::ParseSpecialValue(const rapidjson::Value& json, CAbility* ability) {
    if (json.IsNull()) return;
    for (int i = 0; i < GetJsonArraySize(json); ++i) {
        const rapidjson::Value& item = json[i];
        if (item.IsNull()) continue;
        CAbilityValue* value = CreateVariableList(item["value"], GetJsonStringValueFromDic(item, "type"), ability);
        ability->AddSpecialValue(value, GetJsonStringValueFromDic(item, "key"));
    }
}

// 创建参数列表，json可为float、string、list
CAbilityValue* SkillReaderJson::CreateVariableList(const rapidjson::Value& item, std::string type, CAbility* ability) {
    if (item.IsNull()) return NULL;
    if (item.IsArray()) {
        CAbilityValue::Array array;
        for (int j = 0; j < GetJsonArraySize(item); ++j) {
            if (type == "float")        array.push_back(GetJsonFloatValueFromArray(item, j));
            else if (type == "string")  array.push_back(GetJsonStringValueFromArray(item, j));
        }
        return new CAbilityValue(array);
    }
    else {
        if (item.IsString()) {
            std::string value = item.GetString();
            if (IsJsonReference(value)) {
                std::string newvalue = std::string(value.begin() + 1, value.end());
                return ability->GetSpecialValue(newvalue)->Clone();
            }
        }
        if (type == "float")        return new CAbilityValue(item.GetFloat());
        else if (type == "string")  return new CAbilityValue(item.IsString());
    }
    return NULL;
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
    if (json.IsNull() || !CheckJsonIsKeyNotNull(json, eventName.c_str())) return NULL;
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
    if (json.IsNull() || !CheckJsonIsKeyNotNull(json, eventName.c_str())) return NULL;
    const rapidjson::Value& eventdata = json[eventName.c_str()];
    CModifierEvent* event = new CModifierEvent();
    ParseOperate(eventdata, event, ability);
    return event;
}

void SkillReaderJson::ParseOperate(const rapidjson::Value& json, CEvent* event, CAbility* ability) {
    if (json.IsNull()) return;
    if (CheckJsonIsKeyNotNull(json, "ApplyModifier")) {
        const rapidjson::Value& item = json["ApplyModifier"];
        assert(CheckJsonIsKeyNotNull(item, "ModifierName"));
        COpApplyModifier* operate = new COpApplyModifier(GetJsonStringValueFromDic(item, "ModifierName"));
        ParseOperateTarget(item, operate, ability);
        if (operate) event->AddOperate(operate);
    }
    if (CheckJsonIsKeyNotNull(json, "Heal")) {
        const rapidjson::Value& item = json["Heal"];
        assert(CheckJsonIsKeyNotNull(item, "HealAmount"));
        COpHeal* operate = new COpHeal(CreateVariableList(item["HealAmount"], "float", ability));
        ParseOperateTarget(item, operate, ability);
        if (operate) event->AddOperate(operate);
    }
    if (CheckJsonIsKeyNotNull(json, "Damage")) {
        const rapidjson::Value& item = json["Damage"];
        assert(CheckJsonIsKeyNotNull(item, "Damage"));
        assert(CheckJsonIsKeyNotNull(item, "DamageType"));
        COpDamage* operate = new COpDamage();
        operate->SetDamageType((ABILITY_DAMAGE_TYPE)SKB::GetEnumByString(GetJsonStringValueFromDic(item, "DamageType", "ABILITY_DAMAGE_TYPE_MAGICAL")));
        operate->SetDamage(CreateVariableList(item["Damage"], "float", ability));
        operate->SetCurrentPercent(CreateVariableList(item["CurrentHealthPercentBasedDamage"], "float", ability));
        operate->SetMaxPercent(CreateVariableList(item["MaxHealthPercentBasedDamage"], "float", ability));
        ParseOperateTarget(item, operate, ability);
        if (operate) event->AddOperate(operate);
    }
    if (CheckJsonIsKeyNotNull(json, "Log")) {
        const rapidjson::Value& item = json["Log"];
        COpLog* operate = new COpLog(GetJsonStringValueFromDic(item, "text"));
        ParseOperateTarget(item, operate, ability);
        if (operate) event->AddOperate(operate);
    }
    if (CheckJsonIsKeyNotNull(json, "LinearProjectile")) {
        const rapidjson::Value& item = json["LinearProjectile"];
        COpLinearProjectile* operate = new COpLinearProjectile();
        operate->GetData()->SetEffectName(GetJsonStringValueFromDic(item, "EffectName", ""));
        operate->GetData()->SetMoveSpeed(CreateVariableList(item["MoveSpeed"], "float", ability));
        operate->GetData()->SetStartRadius(CreateVariableList(item["StartRadius"], "float", ability));
        operate->GetData()->SetEndRadius(CreateVariableList(item["EndRadius"], "float", ability));
        operate->GetData()->SetAttachType((MODIFIER_EFFECT_ATTACH_TYPE)SKB::GetEnumByString(GetJsonStringValueFromDic(item, "AttachType", "MODIFIER_EFFECT_ATTACH_TYPE_ORIGIN")));
        operate->GetData()->SetLength(CreateVariableList(item["Distance"], "float", ability));
        operate->GetData()->SetIsProvidesVision(GetJsonBooleanValueFromDic(item, "IsProvidesVision", false));
        operate->GetData()->SetVisionRadius(CreateVariableList(item["VisionRadius"], "float", ability));
        ParseOperateTarget(item, operate, ability);
        if (operate) event->AddOperate(operate);
    }
}

void SkillReaderJson::ParseOperateTarget(const rapidjson::Value& json, COperate* operate, CAbility* ability) {
    if (json.IsNull() || !CheckJsonIsKeyNotNull(json, "Target")) return;
    // 范围搜索
    if (json["Target"].IsObject()) {
        std::string center = GetJsonStringValueFromDic(json, "Center");
        if (center == "TARGET") operate->SetCenter(TARGET_CENTER_TARGET);
        else if (center == "CASTER" ) operate->SetCenter(TARGET_CENTER_CASTER);
        else if (center == "ATTACKER" ) operate->SetCenter(TARGET_CENTER_ATTACKER);
        else if (center == "POINT" ) operate->SetCenter(TARGET_CENTER_POINT);
        else if (center == "PROJECTILE" ) operate->SetCenter(TARGET_CENTER_PROJECTILE);
        
        std::string team_str = GetJsonStringValueFromDic(json["Target"], "Teams", "TARGET_TEAM_NONE");
        operate->SetTeams((TARGET_TEAMS)SKB::GetEnumByString(team_str));
        
        std::string type_str = GetJsonStringValueFromDic(json["Target"], "Types", "TARGET_TYPE_NONE");
        operate->SetTypes((TARGET_TYPES)SKB::GetEnumByString(type_str));
        
        operate->SetRadius(CreateVariableList(json["Target"]["Radius"], "float", ability));
        
        // max targets
        operate->SetMaxTargets(CheckJsonIsKeyNotNull(json, "MaxTargets") ? CreateVariableList(json["MaxTargets"], "float", ability) : NULL);
    }
    // 已存在
    else {
        std::string target = GetJsonStringValueFromDic(json, "Target");
        if (target == "TARGET") operate->SetSingle(TARGET_CENTER_TARGET);
        else if (target == "CASTER" ) operate->SetSingle(TARGET_CENTER_CASTER);
        else if (target == "ATTACKER" ) operate->SetSingle(TARGET_CENTER_ATTACKER);
        operate->SetRadius(0);
    }
}

void SkillReaderJson::ParseModifiers(const rapidjson::Value& json, CAbility* ability) {
    if (!CheckJsonIsKeyNotNull(json, "Modifiers")) return;
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
    modifier->SetIsBuff(GetJsonBooleanValueFromDic(item, "IsBuff"));
    modifier->SetIsDebuff(GetJsonBooleanValueFromDic(item, "IsDeBuff"));
    modifier->SetIsPurgable(GetJsonBooleanValueFromDic(item, "IsPurgable"));
    modifier->SetIsPassive(GetJsonBooleanValueFromDic(item, "IsPassive"));
    modifier->SetIsHidden(GetJsonBooleanValueFromDic(item, "IsHidden"));
    modifier->SetDuration(GetJsonFloatValueFromDic(item, "Duration"));
    modifier->SetThinkInterval(GetJsonFloatValueFromDic(item, "ThinkInterval"));
    modifier->SetIsMulti(GetJsonBooleanValueFromDic(item, "IsMulti"));
    modifier->SetMaxMulti(GetJsonIntValueFromDic(item, "MaxMulti", 1));
    modifier->SetTextureName(GetJsonStringValueFromDic(item, "TextureName"));
    modifier->SetEffectName(GetJsonStringValueFromDic(item, "EffectName"));
    modifier->SetModelName(GetJsonStringValueFromDic(item, "ModelName"));
    // events
    ParseModifierEvent(item, modifier, ability);
    // properties
    if (CheckJsonIsKeyNotNull(item, "Properties")) {
        const rapidjson::Value& itemProperty = item["Properties"];
        for (auto iter = itemProperty.MemberBegin(); iter != itemProperty.MemberEnd(); ++iter) {
            std::string name = iter->name.GetString();
            MODIFIER_ATTRIBUTES property = (MODIFIER_ATTRIBUTES)SKB::GetEnumByString(name);
            float value = iter->value.GetFloat();
            modifier->SetProperty(property, value);
        }
    }
    return modifier;
}
