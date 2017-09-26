//
//  CTrackingProjectile.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTrackingProjectile_hpp
#define CTrackingProjectile_hpp

#include <iostream>
#include "CProjectile.hpp"

class CAbility;
class CAbilityEntity;
class CAbilityValue;
class CTargetSearchType;

class CTrackingProjectileData {
public:
    CTrackingProjectileData() {}
    ~CTrackingProjectileData() {}
private:
    TARGET_LIST targets_;
    std::string effectName_;
    CAbilityValue* moveSpeed_;
    MODIFIER_EFFECT_ATTACH_TYPE attachType_;
    bool isDeleteOnHit_;        // 碰到目标后是否删除
    bool isProvidesVision_;     // 是否提供视野
    CAbilityValue* visionRadius_;        // 视野范围
    CTargetSearchType* targetType_;
    CAbilityEntity* caster_;
    CAbility* ability_;
};

class CTrackingProjectile : public CObject {
public:
    CTrackingProjectile() {}
    ~CTrackingProjectile() {}
};

#endif /* CTrackingProjectile_hpp */
