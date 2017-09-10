//
//  TimeUtil.h
//  SkillLib
//
//  Created by yucong on 2017/9/6.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef TimeUtil_h
#define TimeUtil_h

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

namespace SKB {
    long GetNow() {
        time_t t;
        t = time(NULL);
        return time(&t);
    }
}


#endif /* TimeUtil_h */
