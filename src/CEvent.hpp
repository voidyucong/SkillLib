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

class CEvent : public CObject {
    
public:
    virtual int Execute(CAbilityEntity* entity, CAbility* ability);
    
    CEvent();
    CEvent(EVENT_TYPE type);
    virtual ~CEvent();
    
    void AddOperate(COperate* op);
private:
    EVENT_TYPE type_;
    std::vector<COperate*> operators_;
};

#endif /* CEvent_hpp */
