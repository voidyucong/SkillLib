//
//  CModifier.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifier.h"
#include "CModifierEvent.hpp"
#include "COperate.hpp"

CModifier::CModifier()
: isMulti_(true)
, duration_(0)
, isPassive_(false)
, isHidden_(false)
, isBuff_(false)
, isDebuff_(false)
, isPurgable_(false)
, thinkInterval_(0.f)
, textureName_(NULL)
, effectName_(NULL)
, modelName_(NULL)
{
    
}

CModifier::~CModifier() {
    
}

void CModifier::SetModifierEvent(MODIFIER_EVENT_TYPE type, CModifierEvent* event) {
    this->events_[type] = event;
}

int CModifier::ExecuteEvent(MODIFIER_EVENT_TYPE type) {
    CModifierEvent* event = this->GetModifierEvent(type);
    if (event) {
        return event->Execute();
    }
    return 0;
}

void CModifier::ExecuteOperate() {
    for (COperate* operate : this->operators_) {
        operate->Execute();
    }
}
