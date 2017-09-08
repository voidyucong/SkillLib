//
//  CSchedule.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CSchedule_hpp
#define CSchedule_hpp

#include <stdio.h>
#include <iostream>
#include "CObject.hpp"

class CSchedule final {
public:
    CSchedule();
    CSchedule(CObject* target, CObject::CALLBACK callback, float interval);
    ~CSchedule();
    
    void AddCallback(CObject* target, CObject::CALLBACK callback);
    
    void update(float dt);
private:
    float interval_;
    float elapsed_;
    CObject* target_;
    CObject::CALLBACK callback_;
};


#endif /* CSchedule_hpp */
