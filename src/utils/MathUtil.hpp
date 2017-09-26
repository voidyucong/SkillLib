//
//  MathUtil.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/25.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef MathUtil_hpp
#define MathUtil_hpp

#include <iostream>
#include <math.h>
#include "CObject.hpp"

#define MAX(x,y) (((x) < (y)) ? (y) : (x))

namespace SKB {
    class MathUtil {
    public:
        static double TriangleArea(const CVector& a, const CVector& b, const CVector& c) {
            return fabsf((a.GetX() * b.GetY() + b.GetX() * c.GetY() + c.GetX() * a.GetY() - a.GetX() * c.GetY()
                         - b.GetX() * a.GetY() - c.GetX() * b.GetY()) / 2.0f);
        }
        // 角度转弧度
        static float AngleToRadian(float angle) { return M_PI / 180.f * angle; }
        // 弧度转角度
        static float RadianToAngle(float radian) { return 180.f / M_PI * radian; }

    };
}

#endif /* MathUtil_hpp */
