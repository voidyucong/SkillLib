//
//  CObject.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CObject_hpp
#define CObject_hpp

#include <iostream>
#include <math.h>
#include <vector>

class CAbilityEntity;
typedef std::vector<CAbilityEntity*> TARGET_LIST;

class CVector {
public:
    CVector(): CVector(0.f, 0.f) {}
    CVector(float x, float y): x_(x), y_(y) {}
    CVector(const CVector& other) { x_ = other.x_; y_ = other.y_; }
    ~CVector() {}
    CVector& operator= (const CVector& other) {
        if (&other == this)
            return *this;
        this->x_ = other.x_;
        this->y_ = other.y_;
        return *this;
    }
    CVector operator+ (const CVector& right) const { return CVector(this->x_ + right.x_, this->y_ + right.y_); }
    CVector operator- (const CVector& right) const { return CVector(this->x_ - right.x_, this->y_ - right.y_); }
    
    float GetLength() const { return sqrtf(x_ * x_ + y_ * y_); }
    float GetDistance(const CVector& other) const { return (*this - other).GetLength(); }
    
    void SetX(float x) { x_ = x; }
    void SetY(float y) { y_ = y; }
    float GetX() const { return x_; }
    float GetY() const { return y_; }
private:
    float x_;
    float y_;
};


class CLine {
public:
    CLine(): CLine(0.f, 0.f, 0.f, 0.f, 0.f) {}
    CLine(float lx, float ly, float rx, float ry, float width) { setLine(lx, ly, rx, ry, width); }
    CLine(const CLine& other) { setLine(other.leftpoint.GetX(), other.leftpoint.GetY(), other.rightpoint.GetX(), other.rightpoint.GetY(), other.width); }
    CLine& operator= (const CLine& other) {
        if (&other == this)
            return *this;
        setLine(other.leftpoint.GetX(), other.leftpoint.GetY(), other.rightpoint.GetX(), other.rightpoint.GetY(), other.width);
        return *this;
    }
    void setLine(float lx, float ly, float rx, float ry, float width) {
        leftpoint.SetX(lx);
        leftpoint.SetY(ly);
        rightpoint.SetX(rx);
        rightpoint.SetY(ry);
        this->width = width;
    }
    bool containsPoint(const CVector& point) const {
        return true;
    }
    
    CVector leftpoint;
    CVector rightpoint;
    float width;
};

class CObject {
public:
    typedef void (CObject::*CALLBACK) (float);
public:
    CObject() {}
    ~CObject() {}
};

#endif /* CObject_hpp */
