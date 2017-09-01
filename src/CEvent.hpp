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
#include "SkillTypes.h"

class COperate;

class CEvent {
    
public:
    virtual int Execute();
    
    CEvent();
    CEvent(EVENT_TYPE type);
    virtual ~CEvent();
    
    void AddOperate(COperate* op);
private:
    EVENT_TYPE type_;
    std::vector<COperate*> operators_;
};

#endif /* CEvent_hpp */
