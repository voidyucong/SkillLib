//
//  ReaderJsonUtil.h
//  SkillLib
//
//  Created by yucong on 2017/9/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef ReaderJsonUtil_h
#define ReaderJsonUtil_h

#include <iostream>
#include "CAbilityValue.hpp"
#include "CAbility.hpp"
#include "rapidjson.h"
#include "document.h"

namespace SKB {
    class ReaderJsonUtil {
    public:
        static bool CheckJsonIsKeyValid(const rapidjson::Value& json, const char* key) {
            if (json.IsNull()) return false;
            if (json.FindMember(key) == json.MemberEnd()) return false;
            return true;
        }
        
        static bool CheckJsonIsKeyNotNull(const rapidjson::Value& json, const char* key) {
            if (!CheckJsonIsKeyValid(json, key)) return false;
            if (json[key].IsNull()) return false;
            return true;
        }
        
        static std::string GetJsonStringValueFromDic(const rapidjson::Value& json, const char* key, std::string def = "") {
            if (!CheckJsonIsKeyNotNull(json, key)) return def;
            return json[key].GetString();
        }
        
        static float GetJsonFloatValueFromDic(const rapidjson::Value& json, const char* key, float def = 0.f) {
            if (!CheckJsonIsKeyNotNull(json, key)) return def;
            return json[key].GetFloat();
        }
        
        static int GetJsonIntValueFromDic(const rapidjson::Value& json, const char* key, int def = 0) {
            if (!CheckJsonIsKeyNotNull(json, key)) return def;
            return json[key].GetInt();
        }
        
        static bool GetJsonBooleanValueFromDic(const rapidjson::Value& json, const char* key, bool def = false) {
            if (!CheckJsonIsKeyNotNull(json, key)) return def;
            return json[key].GetBool();
        }
        
        static std::string GetJsonStringValueFromArray(const rapidjson::Value& json, int idx, std::string def = "") {
            if (json.IsNull()) return def;
            if (json[idx].IsNull()) return def;
            return json[idx].GetString();
        }
        
        static float GetJsonFloatValueFromArray(const rapidjson::Value& json, int idx, float def = 0.f) {
            if (json.IsNull()) return def;
            if (json[idx].IsNull()) return def;
            return json[idx].GetFloat();
        }
        
        static int GetJsonIntValueFromArray(const rapidjson::Value& json, int idx, int def = 0) {
            if (json.IsNull()) return NULL;
            if (json[idx].IsNull()) return def;
            return json[idx].GetInt();
        }
        
        static bool GetJsonBooleanValueFromArray(const rapidjson::Value& json, int idx, bool def = false) {
            if (json.IsNull()) return NULL;
            if (json[idx].IsNull()) return def;
            return json[idx].GetBool();
        }
        
        static int GetJsonArraySize(const rapidjson::Value& json) {
            if (json.IsNull()) return NULL;
            return json.Size();
        }
        
        static int GetJsonDicSize(const rapidjson::Value& json) {
            if (json.IsNull()) return NULL;
            return json.Size();
        }
        
        static bool GetJsonBooleanValueFromArray(const rapidjson::Value& json, int idx) {
            if (json.IsNull()) return NULL;
            if (json[idx].IsNull()) return NULL;
            return json[idx].GetBool();
        }
        
        static bool IsJsonReference(std::string name) {
            if (name == "") return false;
            return *(name.begin()) == '%';
        }
        
        // 创建参数列表，json可为float、string、list
//        static CAbilityValue* CreateVariableList(const rapidjson::Value& json, std::string key, std::string type, CAbility* ability) {
//            if (json.IsNull()) return NULL;
//            if (!CheckJsonIsKeyNotNull(json, key.c_str())) return NULL;
//            const rapidjson::Value& item = json[key.c_str()];
//            if (item.IsArray()) {
//                CAbilityValue::Array array;
//                for (int j = 0; j < GetJsonArraySize(item); ++j) {
//                    if (type == "float")        array.push_back(GetJsonFloatValueFromArray(item, j));
//                    else if (type == "string")  array.push_back(GetJsonStringValueFromArray(item, j));
//                }
//                return new CAbilityValue(array);
//            }
//            else {
//                if (item.IsString()) {
//                    std::string value = item.GetString();
//                    if (IsJsonReference(value)) {
//                        std::string newvalue = std::string(value.begin() + 1, value.end());
//                        return ability->GetSpecialValue(newvalue)->Clone();
//                    }
//                }
//                if (type == "float")        return new CAbilityValue(item.GetFloat());
//                else if (type == "string")  return new CAbilityValue(item.IsString());
//            }
//            return NULL;
//        }
        
        template<typename T>
        static CAbilityValue* CreateVariableList(const rapidjson::Value& json, std::string key, CAbility* ability) {
            if (json.IsNull()) return NULL;
            if (!CheckJsonIsKeyNotNull(json, key.c_str())) return NULL;
            const rapidjson::Value& item = json[key.c_str()];
            if (item.IsArray()) {
                CAbilityValue::Array array;
                for (int j = 0; j < GetJsonArraySize(item); ++j) {
                    if (std::is_same<T, float>::value)        array.push_back(GetJsonFloatValueFromArray(item, j));
                    else if (std::is_same<T, std::string>::value)  array.push_back(GetJsonStringValueFromArray(item, j));
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
                if (std::is_same<T, float>::value)        return new CAbilityValue(item.GetFloat());
                else if (std::is_same<T, std::string>::value)  return new CAbilityValue(item.GetString());
            }
            return NULL;
        }
        
        static CAbilityValue* CreateVariableList2(const rapidjson::Value& json, std::string key, std::string type, CAbility* ability) {
            if (type == "string")
                return CreateVariableList<std::string>(json, key, ability);
            else if (type == "float")
                return CreateVariableList<float>(json, key, ability);
            return NULL;
        }
    };
}

#endif /* ReaderJsonUtil_h */
