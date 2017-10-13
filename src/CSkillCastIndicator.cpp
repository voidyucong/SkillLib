//
//  CSkillCastIndicator.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/29.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CSkillCastIndicator.hpp"
#include "CAbilityEntity.hpp"

static CSkillCastIndicator* s_pInstance = NULL;

CSkillCastIndicator::CSkillCastIndicator() {
    
}

CSkillCastIndicator::~CSkillCastIndicator() {
    
}

CSkillCastIndicator* CSkillCastIndicator::getInstance() {
    if (!s_pInstance) s_pInstance = new CSkillCastIndicator();
    return s_pInstance;
}

const CVector& CSkillCastIndicator::GetDirection() {
    if (type_ == INDICATOR_DIRECTION) {
        return direction_;
    }
    else if (type_ == INDICATOR_TARGET) {
        direction_ = (target_->GetPosition() - caster_->GetPosition()).normalize();
        return direction_;
    }
    assert(false);
}

const CVector& CSkillCastIndicator::GetPoint() {
    if (type_ == INDICATOR_POINT) {
        return point_;
    }
    else if (type_ == INDICATOR_TARGET) {
        return target_->GetPosition();
    }
    assert(false);
}
