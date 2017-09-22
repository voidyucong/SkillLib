//
//  CAbilityValue.hpp
//  SkillLib
//
//  Created by yucong on 2017/8/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbilityValue_hpp
#define CAbilityValue_hpp

#include <iostream>
#include <assert.h>
#include <string.h>
#include "CObject.hpp"

class CAbilityValue : public CObject {
    
public:
    typedef std::vector<CAbilityValue> Array;
    typedef std::string String;
private:
    struct {
//        int i;
        float f;
        String s;
        Array a;
    };
    enum {
        NONE, NUMBER, FLOAT, STRING, ARRAY,
    };
public:
    CAbilityValue(): type_(NONE) {}
    CAbilityValue(int value): f(value), type_(FLOAT) {}
    CAbilityValue(float value): f(value), type_(FLOAT) {}
    CAbilityValue(const String& value): s(value), type_(STRING) {}
    CAbilityValue(String&& value): s(std::move(value)), type_(STRING) {}
    CAbilityValue(const char* value): s(value), type_(STRING) {}
    CAbilityValue(const Array& value): a(value), type_(ARRAY) {}
    CAbilityValue(Array&& value): a(std::move(value)), type_(ARRAY) {}
    CAbilityValue(const CAbilityValue& other) {
        if (this != &other) {
            if (other.IsFloat()) SetFloat(other.f);
            else if (other.IsString()) SetString(other.s);
            else if (other.IsArray()) SetArray(other.a);
        }
    }
    ~CAbilityValue() {}
    CAbilityValue* Clone() {
        CAbilityValue* ret = new CAbilityValue();
        if (IsFloat()) ret->SetFloat(f);
        else if (IsString()) ret->SetString(s);
        else if (IsArray()) ret->SetArray(a);
        return ret;
    }
    
    CAbilityValue& operator= (const CAbilityValue& other);
    
//    bool IsInt() const { return type_ == NUMBER; }
    bool IsFloat() const { return type_ == FLOAT; }
    bool IsString() const { return type_ == STRING; }
    bool IsArray() const { return type_ == ARRAY; }

//    void SetInt(int value) { f = (float)value; type_ = NUMBER; }
    void SetFloat(float value) { f = value; type_ = FLOAT; }
    void SetString(const String& value) { s = value; type_ = STRING; }
    void SetArray(const Array& value) { a = value; type_ = ARRAY; }
    
    CAbilityValue* GetArrayValueByIndex(unsigned index);

    template<typename T>
    bool IsType() const;
    template<typename T>
    T& GetValue();
    template<typename T>
    const T& GetValue() const;
    
private:
    unsigned int type_;
};

template<>
inline bool CAbilityValue::IsType<int>() const { return type_ == NUMBER; }

template<>
inline bool CAbilityValue::IsType<float>() const { return type_ == FLOAT; }

template<>
inline bool CAbilityValue::IsType<CAbilityValue::String>() const { return type_ == STRING; }

template<>
inline bool CAbilityValue::IsType<CAbilityValue::Array>() const { return type_ == ARRAY; }


inline CAbilityValue& CAbilityValue::operator= (const CAbilityValue& other) {
//    if (other<int>()) SetInt(other);
    if (other.IsType<float>()) SetFloat(other.f);
    else if (other.IsType<CAbilityValue::String>()) SetString(other.s);
    else if (other.IsType<CAbilityValue::Array>()) SetArray(other.a);
    return *this;
}

inline CAbilityValue* CAbilityValue::GetArrayValueByIndex(unsigned index) {
//    assert(IsArray());
    if (IsArray()) {
        assert(index < a.size());
        return &a[index];
    }
    else {
        return this;
    }
}


//template<>
//inline int CAbilityValue::GetValue<int>() { assert(IsType<float>()); return f; }

template<>
inline float& CAbilityValue::GetValue<float>() { assert(IsType<float>()); return f; }

template<>
inline CAbilityValue::String & CAbilityValue::GetValue<std::string>() { assert(IsType<CAbilityValue::String>()); return s; }

template<>
inline CAbilityValue::Array& CAbilityValue::GetValue<CAbilityValue::Array>() { assert(IsType<CAbilityValue::Array>()); return a; }

//template<>
//inline const int& CAbilityValue::GetValue<int>() const { assert(IsType<int>()); return i; }

template<>
inline const float& CAbilityValue::GetValue<float>() const { assert(IsType<float>()); return f; }

template<>
inline const CAbilityValue::String& CAbilityValue::GetValue<std::string>() const { assert(IsType<CAbilityValue::String>()); return s; }

template<>
inline const CAbilityValue::Array& CAbilityValue::GetValue<CAbilityValue::Array>() const { assert(IsType<CAbilityValue::Array>()); return a; }

#endif /* CAbilityValue_hpp */
