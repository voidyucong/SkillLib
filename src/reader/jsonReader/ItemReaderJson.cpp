//
//  ItemReaderJson.cpp
//  SkillLib
//
//  Created by yucong on 2017/10/17.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "ItemReaderJson.hpp"
#include "SkillReaderJson.hpp"
#include "CItem.hpp"
#include "CItemData.hpp"
#include "SkillTypesMapping.h"

using namespace SKB;
#define RUTL ReaderJsonUtil
static ItemReaderJson* s_pInstance = NULL;

ItemReaderJson::ItemReaderJson() {
    
}

ItemReaderJson::~ItemReaderJson() {
    
}

ItemReaderJson* ItemReaderJson::getInstance() {
    if (!s_pInstance) s_pInstance = new ItemReaderJson();
    return s_pInstance;
}

CItem* ItemReaderJson::ItemFromFile(std::string fileName) {
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
    
    CItem* item = CreateItem(json);
    
    free((void*)pBuf);
    
    return item;
}

CItem* ItemReaderJson::CreateItem(const rapidjson::Value& json) {
    if (json.IsNull()) return NULL;
    CItem* item = new CItem();
    // special value
    if (json.FindMember("AbilitySpecial") != json.MemberEnd())
        SkillReaderJson::getInstance()->ParseSpecialValue(json["AbilitySpecial"], item);
    
    // name
    item->SetName(RUTL::GetJsonStringValueFromDic(json, "name"));
    // AbilityBehavior
    long behavior = 0;
    for (int i = 0; i < RUTL::GetJsonArraySize(json["AbilityBehavior"]); ++i) {
        std::string behaviorstr = RUTL::GetJsonStringValueFromArray(json["AbilityBehavior"], i);
        behavior |= SKB::GetEnumByString(behaviorstr);
    }
    item->SetBehavior(behavior);
    // damage type
    item->SetDamageType((ABILITY_DAMAGE_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "AbilityUnitDamageType")));
    // texture name
    item->SetTextureIconName(RUTL::GetJsonStringValueFromDic(json, "AbilityTextureName"));
    // cast width
    item->SetCastWidth(RUTL::CreateVariableList<float>(json, "AbilityCastWidth", item));
    // cast range
    item->SetCastRange(RUTL::CheckJsonIsKeyNotNull(json, "AbilityCastRange") ? RUTL::CreateVariableList<float>(json, "AbilityCastRange", item) : NULL);
    // cast point
    item->SetCastPoint(RUTL::CreateVariableList<float>(json, "AbilityCastPoint", item));
    if (behavior & ABILITY_BEHAVIOR_AOE) {
        // aoe range
        item->SetAoeRange(RUTL::CreateVariableList<float>(json, "AoeRadius", item));
    }
    // cooldown
    item->SetBaseCooldown(RUTL::CreateVariableList<float>(json, "AbilityCooldown", item));
    // mana cost
    item->SetManaCost(RUTL::CreateVariableList<float>(json, "AbilityManaCost", item));
    // damage
    item->SetDamage(RUTL::CreateVariableList<float>(json, "AbilityDamage", item));
    
    // Event
    SkillReaderJson::getInstance()->ParseAbilityEvent(json, item);
    
    // Modifiers
    SkillReaderJson::getInstance()->ParseModifiers(json, item);
    
    // Item Info
    ParseItem(json, item);
    return item;
}

void ItemReaderJson::ParseItem(const rapidjson::Value& json, CItem* item) {
    CItemData* data = new CItemData();
    data->SetId(RUTL::GetJsonIntValueFromDic(json, "ID"));
    data->SetCost(RUTL::GetJsonIntValueFromDic(json, "ItemCost"));
    data->SetShopFlags((ITEM_TYPE)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "ItemShopTags")));
    data->SetQuality((ITEM_QUALITY)SKB::GetEnumByString(RUTL::GetJsonStringValueFromDic(json, "ItemQuality")));
    if (json.FindMember("ItemRequirements") != json.MemberEnd()) {
        for (int i = 0; i < json["ItemRequirements"].Size(); ++i) {
            data->AddRequirements(RUTL::GetJsonIntValueFromArray(json["ItemRequirements"], i));
        }
    }
    if (json.FindMember("DefaultModifiers") != json.MemberEnd()) {
        for (int i = 0; i < json["DefaultModifiers"].Size(); ++i) {
            data->AddDefaultModifiers(RUTL::GetJsonStringValueFromArray(json["DefaultModifiers"], i));
        }
    }
    item->SetItemData(data);
}
