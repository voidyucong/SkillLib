//
//  CModifierEvent.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifierEvent.hpp"
#include "COperate.hpp"

CModifierEvent::CModifierEvent() {
    
}

CModifierEvent::~CModifierEvent() {
    
}

int CModifierEvent::Execute(CAbilityEntity *entity, CAbility *ability) {
    return CEvent::Execute(entity, ability);
}

CModifierEvent* CModifierEvent::Clone() {
    CModifierEvent* event = new CModifierEvent();
    for (COperate* op : operators_) {
        event->AddOperate(op->Clone());
    }
    return event;
}
