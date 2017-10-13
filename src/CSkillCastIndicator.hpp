//
//  CSkillCastIndicator.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/29.
//  Copyright © 2017年 yucong. All rights reserved.
//  技能释放指示器
//  可指示方向、点、目标实体

#ifndef CSkillCastIndicator_hpp
#define CSkillCastIndicator_hpp

#include <iostream>
#include "CObject.hpp"

class CAbilityEntity;

class CSkillCastIndicator {
    enum {
        INDICATOR_NONE,
        INDICATOR_DIRECTION,
        INDICATOR_POINT,
        INDICATOR_TARGET,
    };
public:
    CSkillCastIndicator();
    ~CSkillCastIndicator();
    static CSkillCastIndicator* getInstance();
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    void Clear() { type_ = INDICATOR_NONE; }
    uint GetType() { return type_; }
    
    void SetDirection(const CVector& direction) { type_ = INDICATOR_DIRECTION; direction_ = direction; }
    const CVector& GetDirection();
    void SetPoint(const CVector& point) { type_ = INDICATOR_POINT; point_ = point; }
    const CVector& GetPoint();
    void SetTarget(CAbilityEntity* target) { type_ = INDICATOR_TARGET; target_ = target; }
    CAbilityEntity* GetTarget() { return target_; }
private:
    uint type_;
    CVector direction_;         // 方向
    CVector point_;             // 点
    CAbilityEntity* target_;    // 选中的目标
    
    CAbilityEntity* caster_;
};

#endif /* CSkillCastIndicator_hpp */
