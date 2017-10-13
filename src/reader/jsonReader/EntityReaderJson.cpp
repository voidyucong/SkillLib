//
//  EntityReaderJson.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "EntityReaderJson.hpp"
#include "CAbility.hpp"
#include "CAbilityValue.hpp"
#include "CAbilityEntity.hpp"
#include "SkillTypesMapping.h"

using namespace SKB;
#define RUTL ReaderJsonUtil

static EntityReaderJson* s_pInstance = NULL;

EntityReaderJson::EntityReaderJson() {
    
}

EntityReaderJson::~EntityReaderJson() {
    
}

EntityReaderJson* EntityReaderJson::getInstance() {
    if (!s_pInstance) {
        s_pInstance = new EntityReaderJson();
    }
    return s_pInstance;
}

CAbilityEntity* EntityReaderJson::EntityFromFile(std::string fileName) {
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
    
    CAbilityEntity* entity = CreateEntity(json);
    
    free((void*)pBuf);
    
    return entity;
}

CAbilityEntity* EntityReaderJson::CreateEntity(const rapidjson::Value& json) {
    if (json.IsNull()) return NULL;
    
    CAbilityEntity* entity = new CAbilityEntity();
    CAbilityEntityData* data = new CAbilityEntityData();
    
    data->SetName(RUTL::GetJsonStringValueFromDic(json, "Name", ""));
    data->SetType((ENTITY_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "type", "")));
    data->SetLevel(RUTL::GetJsonIntValueFromDic(json, "Level", 1));
    data->SetModelFile(RUTL::GetJsonStringValueFromDic(json, "Model"));
    data->SetModelScale(RUTL::GetJsonFloatValueFromDic(json, "ModelScale", 1.f));
    data->SetMinimapIcon(RUTL::GetJsonStringValueFromDic(json, "MinimapIcon", ""));
    data->SetMinimapIconSize(RUTL::GetJsonFloatValueFromDic(json, "MinimapIconSize"));
    float width = RUTL::GetJsonFloatValueFromDic(json, "BoundSize");
    data->SetSize(CSize(width, width));
    data->SetIsIsNeutralUnitType(RUTL::GetJsonBooleanValueFromDic(json, "IsNeutralUnitType", false));
    data->SetIsAutoAttacksByDefault(RUTL::GetJsonBooleanValueFromDic(json, "AutoAttacksByDefault", false));
    data->SetSoundFile(RUTL::GetJsonStringValueFromDic(json, "SoundSet", ""));
    data->SetGameSoundsFile(RUTL::GetJsonStringValueFromDic(json, "GameSoundsFile", ""));
    data->SetAbilityLayout(RUTL::GetJsonIntValueFromDic(json, "AbilityLayout", 0));
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability1", ""), 0);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability2", ""), 1);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability3", ""), 2);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability4", ""), 3);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability5", ""), 4);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability6", ""), 6);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability7", ""), 7);
    data->SetAbility(RUTL::GetJsonStringValueFromDic(json, "Ability8", ""), 8);
    data->SetAttackCapability((ENTITY_ATTACK_CAPABILITY)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AttackCapabilities", "")));
    data->SetMovementCapability((ENTITY_MOVEMENT_CAPABILITY)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "MovementCapabilities", "")));
    data->SetAttackDamageMin(RUTL::GetJsonFloatValueFromDic(json, "AttackDamageMin", 0));
    data->SetAttackDamageMax(RUTL::GetJsonFloatValueFromDic(json, "AttackDamageMax", 0));
    data->SetAttackRate(RUTL::GetJsonFloatValueFromDic(json, "AttackRate", 0));
    
    
    data->SetAttackAnimationPoint(RUTL::GetJsonFloatValueFromDic(json, "AttackAnimationPoint", 0));
    data->SetAttackAcquisitionRange(RUTL::GetJsonFloatValueFromDic(json, "AttackAcquisitionRange", 0));
    data->SetAttackRange(RUTL::GetJsonFloatValueFromDic(json, "AttackRange", 0));
    data->SetAttackRangeBuffer(RUTL::GetJsonFloatValueFromDic(json, "AttackRangeBuffer", 0));
    data->SetProjectileModel(RUTL::GetJsonStringValueFromDic(json, "ProjectileModel", ""));
    data->SetProjectileSpeed(RUTL::GetJsonFloatValueFromDic(json, "ProjectileSpeed", 0));
    data->SetPrimary((ENTITY_ATTRIBUTE_PRIMARY)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AttributePrimary", "")));
    data->SetBaseStrength(RUTL::GetJsonFloatValueFromDic(json, "BaseStrength", 0));
    data->SetStrengthGain(RUTL::GetJsonFloatValueFromDic(json, "StrengthGain", 0));
    data->SetBaseIntelligence(RUTL::GetJsonFloatValueFromDic(json, "BaseIntelligence", 0));
    data->SetIntelligenceGain(RUTL::GetJsonFloatValueFromDic(json, "IntelligenceGain", 0));
    data->SetBaseAgility(RUTL::GetJsonFloatValueFromDic(json, "BaseAgility", 0));
    data->SetAgilityGain(RUTL::GetJsonFloatValueFromDic(json, "AgilityGain", 0));
    data->SetBaseHP(RUTL::GetJsonFloatValueFromDic(json, "BaseHP", 0));
    data->SetHPGain(RUTL::GetJsonFloatValueFromDic(json, "HPGain", 0));
    data->SetHPRegen(RUTL::GetJsonFloatValueFromDic(json, "HPRegen", 0));
    data->SetBaseMana(RUTL::GetJsonFloatValueFromDic(json, "BaseMana", 0));
    data->SetManaGain(RUTL::GetJsonFloatValueFromDic(json, "ManaGain", 0));
    data->SetManaRegen(RUTL::GetJsonFloatValueFromDic(json, "ManaRegen", 0));
    data->SetStartingMana(RUTL::GetJsonFloatValueFromDic(json, "StartingMana", 0));
    data->SetDamageGain(RUTL::GetJsonFloatValueFromDic(json, "DamageGain", 0));
    data->SetArmorPhysical(RUTL::GetJsonFloatValueFromDic(json, "ArmorPhysical", 0));
    data->SetArmorGain(RUTL::GetJsonFloatValueFromDic(json, "ArmorGain", 0));
    data->SetMagicalResist(RUTL::GetJsonFloatValueFromDic(json, "MagicalResist", 0));
    data->SetMagicResistGain(RUTL::GetJsonFloatValueFromDic(json, "MagicResistGain", 0));
    data->SetMovementSpeed(RUTL::GetJsonFloatValueFromDic(json, "MovementSpeed", 0));
    data->SetMoveSpeedGain(RUTL::GetJsonFloatValueFromDic(json, "MoveSpeedGain", 0));
    data->SetPhysicalLifesteal(RUTL::GetJsonFloatValueFromDic(json, "PhysicalLifesteal", 0));
    data->SetMagicalLifesteal(RUTL::GetJsonFloatValueFromDic(json, "MagicalLifesteal", 0));
    data->SetBasePhysicalPenetrate(RUTL::GetJsonFloatValueFromDic(json, "BasePhysicalPenetrate", 0));
    data->SetMagicalPenetrateGain(RUTL::GetJsonFloatValueFromDic(json, "PhysicalPenetrateGain", 0));
    data->SetBaseMagicalPenetrate(RUTL::GetJsonFloatValueFromDic(json, "BaseMagicalPenetrate", 0));
    data->SetMagicalPenetrateGain(RUTL::GetJsonFloatValueFromDic(json, "MagicalPenetrateGain", 0));
    data->SetXPGain(RUTL::GetJsonFloatValueFromDic(json, "XPGain", 0));
    data->SetVisionRange(RUTL::GetJsonFloatValueFromDic(json, "VisionRange", 0));
    data->SetAttackDamageMin(RUTL::GetJsonFloatValueFromDic(json, "AttackDamageMin", 0));
    data->SetAttackDamageMax(RUTL::GetJsonFloatValueFromDic(json, "AttackDamageMax", 0));
    data->SetAttackRate(RUTL::GetJsonFloatValueFromDic(json, "AttackRate", 0));
    data->SetAttackAnimationPoint(RUTL::GetJsonFloatValueFromDic(json, "AttackAnimationPoint", 0));
    data->SetAttackAcquisitionRange(RUTL::GetJsonFloatValueFromDic(json, "AttackAcquisitionRange", 0));
    data->SetAttackRange(RUTL::GetJsonFloatValueFromDic(json, "AttackRange", 0));
    data->SetAttackRangeBuffer(RUTL::GetJsonFloatValueFromDic(json, "AttackRangeBuffer", 0));
    data->SetProjectileSpeed(RUTL::GetJsonFloatValueFromDic(json, "ProjectileSpeed", 0));
    data->SetCollisionRadius(RUTL::GetJsonFloatValueFromDic(json, "RingRadius", 0));
    data->SetHealthBarOffset(RUTL::GetJsonIntValueFromDic(json, "HealthBarOffset", -1));
    data->SetScript(RUTL::GetJsonStringValueFromDic(json, "vscript", ""));
    
    entity->SetData(data);
    
    return entity;
}
