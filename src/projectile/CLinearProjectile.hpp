//
//  CLinearProjectile.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CLinearProjectile_hpp
#define CLinearProjectile_hpp

#include <iostream>
#include "CObject.hpp"
#include "SkillTypes.h"

class CAbilityValue;

class CLinearProjectileData {
public:
    CLinearProjectileData() {}
    ~CLinearProjectileData() {}
    
    void SetEffectName(std::string name) { effectName_ = name; }
    void SetMoveSpeed(CAbilityValue* value) { moveSpeed_ = value; }
    void SetStartRadius(CAbilityValue* value) { startRadius_ = value; }
    void SetEndRadius(CAbilityValue* value) { endRadius_ = value; }
    void SetDistance(CAbilityValue* value) { distance_ = value; }
    void SetAttachType(MODIFIER_EFFECT_ATTACH_TYPE value) { attachType_ = value; }
    void SetIsProvidesVision(bool value) { isProvidesVision_ = value; }
    void SetVisionRadius(CAbilityValue* value) { visionRadius_ = value; }
    
    std::string GetEffectName() { return effectName_; }
    CAbilityValue* GetMoveSpeed() { return moveSpeed_; }
    CAbilityValue* GetStartRadius() { return startRadius_; }
    CAbilityValue* GetEndRadius() { return endRadius_; }
    CAbilityValue* GetDistance() { return distance_; }
    MODIFIER_EFFECT_ATTACH_TYPE GetAttachType() { return attachType_; }
    bool GetIsProvidesVision() { return isProvidesVision_; }
    CAbilityValue* GetVisionRadius() { return visionRadius_; }
private:
    std::string effectName_;
    CAbilityValue* moveSpeed_;
    CAbilityValue* startRadius_;
    CAbilityValue* endRadius_;
    CAbilityValue* distance_;
    MODIFIER_EFFECT_ATTACH_TYPE attachType_;
    bool isProvidesVision_;     // 是否提供视野
    CAbilityValue* visionRadius_;        // 视野范围
};


class CLinearProjectile : public CObject {
public:
    CLinearProjectile() {}
    ~CLinearProjectile() {}
};

#endif /* CLinearProjectile_hpp */
