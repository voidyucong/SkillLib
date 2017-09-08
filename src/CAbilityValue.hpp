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

class CAbilityValue final {
    
public:
    typedef std::vector<CAbilityValue> Array;
    typedef std::string String;
private:
    union {
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
    CAbilityValue(const CAbilityValue& instance) {
        if (this != &instance) {
//            if (instance.IsInt()) SetInt(instance.i);
            if (instance.IsFloat()) SetFloat(instance.f);
            else if (instance.IsString()) SetString(instance.s);
            else if (instance.IsArray()) SetArray(instance.a);
        }
    }
    ~CAbilityValue() {}
    
    CAbilityValue& operator= (const CAbilityValue& instance);
    
//    bool IsInt() const { return type_ == NUMBER; }
    bool IsFloat() const { return type_ == FLOAT; }
    bool IsString() const { return type_ == STRING; }
    bool IsArray() const { return type_ == ARRAY; }

//    void SetInt(int value) { i = value; type_ = NUMBER; }
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


inline CAbilityValue& CAbilityValue::operator= (const CAbilityValue& instance) {
//    if (instance.IsType<int>()) SetInt(instance.i);
    if (instance.IsType<float>()) SetFloat(instance.f);
    else if (instance.IsType<CAbilityValue::String>()) SetString(instance.s);
    else if (instance.IsType<CAbilityValue::Array>()) SetArray(instance.a);
    return *this;
}

inline CAbilityValue* CAbilityValue::GetArrayValueByIndex(unsigned index) {
    assert(IsArray());
    assert(index < a.size());
    return &a[index];
}


//template<>
//inline int& CAbilityValue::GetValue<int>() { assert(IsType<int>()); return i; }

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
