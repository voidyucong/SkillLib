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
#include <float.h>

#define MAX(x,y) (((x) < (y)) ? (y) : (x))

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
    CVector operator+ (float a) const { return CVector(this->x_ + a, this->y_ + a); }
    CVector operator- (float a) const { return CVector(this->x_ - a, this->y_ - a); }
    CVector operator* (float a) const { return CVector(this->x_ * a, this->y_ * a); }
    CVector operator/ (float a) const { return CVector(this->x_ / a, this->y_ / a); }
    
    inline float dot(const CVector& other) const { return x_*other.x_ + y_*other.y_; };
    inline float cross(const CVector& other) const { return x_*other.y_ - y_*other.x_; };
    CVector normalize() const;
    inline float getRadian() const {
        return atan2f(y_, x_);
    };
    float getRadian(const CVector& other) const;
    float GetLength() const { return sqrtf(x_ * x_ + y_ * y_); }
    float GetDistance(const CVector& other) const { return (*this - other).GetLength(); }
    inline CVector rotate(const CVector& other) const { return CVector(x_*other.x_ - y_*other.y_, x_*other.y_ + y_*other.x_); };
    // pivot 旋转基准点
    // angle 弧度
    CVector rotateByAngle(const CVector& pivot, float angle) const;
    
    static inline CVector forAngle(const float a)
    {
        return CVector(cosf(a), sinf(a));
    }
    
    void SetX(float x) { x_ = x; }
    void SetY(float y) { y_ = y; }
    float GetX() const { return x_; }
    float GetY() const { return y_; }
private:
    float x_;
    float y_;
};

class CSize {
public:
    CSize() {}
    CSize(float w, float h): width(w), height(h) {}
    float width;
    float height;
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


class CRect {
public:
    CRect(): CRect(0.f, 0.f, 0.f, 0.f) {}
    CRect(float width, float height, float x, float y) { size_.width = width; size_.height = height; origin_.SetX(x); origin_.SetY(y); }
    ~CRect() {}
    const CSize& GetSize() const { return size_; }
    const CVector& GetOrigin() const { return origin_; }
    float getMaxX() const { return (float)(origin_.GetX() + size_.width); }
    float getMidX() const { return (float)(origin_.GetX() + size_.width / 2.0); }
    float getMinX() const { return origin_.GetX(); }
    float getMaxY() const { return origin_.GetY() + size_.height; }
    float getMidY() const { return (float)(origin_.GetY() + size_.height / 2.0); }
    float getMinY() const { return origin_.GetY(); }
    bool ContainsPoint(const CVector& point) const;
    bool IntersectsRect(const CRect& rect) const;
    
private:
    CSize size_;
    CVector origin_;
};

class CCircle {
public:
    CCircle() {}
    CCircle(const CVector& center, float radius): center_(center), radius_(radius) {}
    CCircle(CRect rect);
    ~CCircle() {}
    void SetCenter(CVector center) { center_ = center; }
    const CVector& GetCenter() const { return center_; }
    float GetRadius() const { return radius_; }
    
    bool IntersectsCircel(const CCircle& other) const {
        return center_.GetDistance(other.center_) <= (radius_ + other.radius_);
    }
    // 算法详见https://www.zhihu.com/question/24251545 Milp Yip的回答
    bool IntersectsRect(const CRect& rect) const;
    bool IntersectsPoint(const CVector& point) const {
        return center_.GetDistance(point) <= radius_;
    }
private:
    CVector center_;
    float radius_;
};

class CObject {
public:
    typedef void (CObject::*CALLBACK) (float);
public:
    CObject() {}
    ~CObject() {}
};

#endif /* CObject_hpp */
