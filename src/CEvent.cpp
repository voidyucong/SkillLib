//
//  CEvent.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CEvent.hpp"
#include "COperate.hpp"

CEvent::CEvent()
{
    
}

CEvent::CEvent(EVENT_TYPE type)
: type_(type)
{
    
}

CEvent::~CEvent() {
    for (auto op : operators_) {
        delete op;
    }
}

int CEvent::Execute() {
    int ok = 1;
    for (COperate* op : operators_) {
        ok &= op->Execute();
    }
    return ok;
}

void CEvent::AddOperate(COperate* op) {
    operators_.push_back(op);
}
