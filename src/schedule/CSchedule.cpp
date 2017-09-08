//
//  CSchedule.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CSchedule.h"

CSchedule::CSchedule()
: interval_(0.f)
, elapsed_(0.f)
{
    
}

CSchedule::CSchedule(CObject* target, CObject::CALLBACK callback, float interval)
: target_(target)
, callback_(callback)
, interval_(interval)
, elapsed_(0.f)
{
    
}

CSchedule::~CSchedule() {
    
}

void CSchedule::AddCallback(CObject* target, CObject::CALLBACK callback) {
    target_ = target;
    callback_ = callback;
}

void CSchedule::update(float dt) {
    elapsed_ += dt;
    if (elapsed_ >= interval_) {
        if (target_ && callback_) {
            (target_->*callback_)(dt);
        }
        elapsed_ = 0.f;
    }
}
