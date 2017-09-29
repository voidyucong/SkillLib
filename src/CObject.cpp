//
//  CObject.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CObject.hpp"
#include "MathUtil.hpp"

#pragma mark -
#pragma mark CVector

CVector CVector::normalize() const {
    float length = GetLength();
    if(length == 0.) return CVector(1.f, 0);
    return *this / GetLength();
}

float CVector::getRadian(const CVector& other) const
{
//    CVector a2 = normalize();
//    CVector b2 = other.normalize();
//    float angle = atan2f(a2.cross(b2), a2.dot(b2));
//    if( fabs(angle) < FLT_EPSILON ) return 0.f;
//    return angle;
    float x = fabsf(other.x_ - x_);
    float y = fabsf(other.y_ - y_);
    return atanf(y / x);
}

// pivot 旋转基准点
// angle 弧度
CVector CVector::rotateByAngle(const CVector& pivot, float angle) const {
    return pivot + (*this - pivot).rotate(CVector::forAngle(angle));
}

#pragma mark -
#pragma mark CRect

bool CRect::ContainsPoint(const CVector& point) const
{
    bool bRet = false;
    
    if (point.GetX() >= getMinX() && point.GetX() <= getMaxX()
        && point.GetY() >= getMinY() && point.GetY() <= getMaxY())
    {
        bRet = true;
    }
    
    return bRet;
}

bool CRect::IntersectsRect(const CRect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
             getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

#pragma mark -
#pragma mark CCircle

CCircle::CCircle(CRect rect)
: center_(CVector(rect.GetOrigin().GetX() + rect.GetSize().width/2, rect.GetOrigin().GetY() + rect.GetSize().height/2))
, radius_(sqrtf(rect.GetSize().width/2 * rect.GetSize().width/2 + rect.GetSize().height/2 * rect.GetSize().height/2))
{
}

// 算法详见https://www.zhihu.com/question/24251545 Milp Yip的回答
bool CCircle::IntersectsRect(const CRect& rect) const {
    CVector rectCenter(rect.GetOrigin().GetX() + rect.GetSize().width/2, rect.GetOrigin().GetY() + rect.GetSize().height/2);
    CVector quartile(fabsf(center_.GetX() - rectCenter.GetX()), fabsf(center_.GetY() - rectCenter.GetY()));  // 第一象限
    CVector shortage(MAX(quartile.GetX() - rect.GetSize().width/2, 0), MAX(quartile.GetY() - rect.GetSize().height/2, 0));
    return shortage.dot(shortage) <= radius_ * radius_;
}
