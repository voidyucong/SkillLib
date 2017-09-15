//
//  CTargetPoint.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/15.
//  Copyright © 2017年 yucong. All rights reserved.
//
//  点目标的位置

#ifndef CTargetPoint_hpp
#define CTargetPoint_hpp

#include <iostream>
#include "CObject.hpp"

class CTargetPoint : public CObject {
public:
    CTargetPoint();
    ~CTargetPoint();
private:
    int x_;
    int y_;
};

#endif /* CTargetPoint_hpp */
