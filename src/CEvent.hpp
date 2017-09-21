//
//  CEvent.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CEvent_hpp
#define CEvent_hpp

#include <vector>
#include "CObject.hpp"
#include "SkillTypes.h"

class COperate;
class CAbility;
class CAbilityEntity;
class CTargetStack;

class CEvent : public CObject {
    
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack);
    
    CEvent();
    CEvent(EVENT_TYPE type);
    virtual ~CEvent();
    CEvent* Clone();
    
    void AddOperate(COperate* op);
protected:
    std::vector<COperate*> operators_;
};

#endif /* CEvent_hpp */
