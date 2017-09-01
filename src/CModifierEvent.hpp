//
//  CModifierEvent.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CModifierEvent_hpp
#define CModifierEvent_hpp

#include <vector>
#include "CEvent.hpp"

class COperate;

class CModifierEvent : public CEvent {
public:
    virtual int Execute();
    
    CModifierEvent();
    virtual ~CModifierEvent();
private:
    std::vector<COperate*> operators_;
};

#endif /* CModifierEvent_hpp */
