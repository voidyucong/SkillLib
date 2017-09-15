//
//  TimeUtil.h
//  SkillLib
//
//  Created by yucong on 2017/9/6.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef TimeUtil_h
#define TimeUtil_h

#include <iostream>
#include <stdio.h>
//#include <stdarg.h>
//#include <time.h>
#include <sys/time.h>

namespace SKB {
    class TimeUtil {
    public:
        static long GetNow() {
            time_t t;
            t = time(NULL);
            return time(&t);
        }
        
        static double GetSeconds() {
            struct timeval now;
            gettimeofday(&now, NULL);
            return (double)now.tv_sec + (double)now.tv_usec / 1000000.f;
        }
    };
}


#endif /* TimeUtil_h */
