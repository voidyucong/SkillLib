//
//  CEvent.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CEvent.hpp"
#include "COperate.hpp"
#include "CAbility.hpp"
#include "CTargetStack.hpp"

CEvent::CEvent()
{
    
}

CEvent::~CEvent() {
    for (auto op : operators_) {
        delete op;
    }
    operators_.clear();
}

int CEvent::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    int ok = 1;
    for (COperate* op : operators_) {
        ok &= op->Execute(entity, ability, parentStack);
    }
    return ok;
}

void CEvent::AddOperate(COperate* op) {
    operators_.push_back(op);
}

CEvent* CEvent::Clone() {
    CEvent* event = new CEvent();
    for (COperate* op : operators_) {
        event->AddOperate(op->Clone());
    }
    return event;
}
