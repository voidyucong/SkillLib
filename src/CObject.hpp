//
//  CObject.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CObject_hpp
#define CObject_hpp

#include <stdio.h>

class CObject {
public:
    typedef void (CObject::*CALLBACK) (float);
public:
    CObject() {}
    ~CObject() {}
};

#endif /* CObject_hpp */
