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
//#include <stdarg.h>
//#include <time.h>
#include <sys/time.h>

namespace SKB {
    long GetNow() {
        time_t t;
        t = time(NULL);
        return time(&t);
    }
    
    double GetSeconds() {
        struct timeval now;
        gettimeofday(&now, NULL);
        return now.tv_sec + now.tv_usec / 1000000.f;
    }
}


#endif /* TimeUtil_h */
