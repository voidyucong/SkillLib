//
//  CAbility.cpp
//  SkillLib
//
//  Created by yucong on 2017/8/28.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbility.hpp"
#include <assert.h>
#include "CEvent.hpp"
#include "CAbilityValue.hpp"

CAbility::CAbility() {
    
}


CAbility::~CAbility() {
    // delete events
    for (auto iter = events_.begin(); iter != events_.end(); iter++) {
        delete iter->second;
    }
    
    // delete special value
    for (auto iter = specials_.begin(); iter != specials_.end(); iter++) {
        delete iter->second;
    }
}

void CAbility::Cast() {
    this->ExecutEvent(EVENT_TYPE_ON_SPELL_START);
}


// events
void CAbility::SetEvent(EVENT_TYPE type, CEvent* event) {
    events_[type] = event;
}

int CAbility::ExecutEvent(EVENT_TYPE type) {
    CEvent* event = events_[type];
    assert(event);
    return event->Execute();
}


// special value
void CAbility::SetSpecialValue(const char* key, CAbilityValue* value) {
    specials_[key] = value;
}

CAbilityValue* CAbility::GetLevelSpecialValueFor(const char* key, int level) {
    assert(key);
    CAbilityValue* value = specials_[key];
    assert(value);
    assert(value->IsType<CAbilityValue::Array>());
    assert(value->GetValue<CAbilityValue::Array>().size() > level - 1);
    return value->GetArrayValueByIndex(level - 1);
}
