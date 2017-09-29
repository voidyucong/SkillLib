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
class CTargetStack;

class CTrackingProjectileData {
public:
    CTrackingProjectileData(): moveSpeed_(0), castRadius_(0), visionRadius_(0) {}
    ~CTrackingProjectileData();
    
    CTrackingProjectileData* Clone();
    
    void SetEffectName(std::string name) { effectName_ = name; }
    void SetMoveSpeed(CAbilityValue* value) { moveSpeed_ = value; }
    void SetAttachType(MODIFIER_EFFECT_ATTACH_TYPE value) { attachType_ = value; }
    void SetIsProvidesVision(bool value) { isProvidesVision_ = value; }
    void SetVisionRadius(CAbilityValue* value) { visionRadius_ = value; }
    void SetCollisionSize(CSize size) { collisionSize_ = size; }
    void SetCastRadius(CAbilityValue* value) { castRadius_ = value; }
    
    std::string GetEffectName() { return effectName_; }
    CAbilityValue* GetMoveSpeed() { return moveSpeed_; }
    MODIFIER_EFFECT_ATTACH_TYPE GetAttachType() { return attachType_; }
    bool GetIsProvidesVision() { return isProvidesVision_; }
    CAbilityValue* GetVisionRadius() { return visionRadius_; }
    const CSize& GetCollisionSize() { return collisionSize_; }
    CAbilityValue* GetCastRadius() { return castRadius_; }
private:
    std::string effectName_;
    CAbilityValue* moveSpeed_;
    CAbilityValue* castRadius_;          // 范围
    CSize collisionSize_;
    MODIFIER_EFFECT_ATTACH_TYPE attachType_;
    bool isProvidesVision_;     // 是否提供视野
    CAbilityValue* visionRadius_;        // 视野范围
};

class CTrackingProjectile : public CProjectile {
public:
    CTrackingProjectile();
    CTrackingProjectile(CTrackingProjectileData* data);
    ~CTrackingProjectile();
    void Update(float dt);
    void Execute();
    void Destroy();
    void DoCollision();
    CTrackingProjectileData* GetData() { return data_; }
    
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    void SetTarget(CAbilityEntity* target) { target_ = target; }
    void SetAbility(CAbility* ability) { ability_ = ability; }
    void SetCastPosition(const CVector& castPosition) { castPosition_ = castPosition; currentPosition_ = castPosition; }
    
    CAbilityEntity* GetCaster() { return caster_; }
    CAbilityEntity* GetTarget() { return target_; }
    CAbility* GetAbility() { return ability_; }
    const CVector& GetCastPosition() { return castPosition_; }
    double GetCastTime() { return castTimestamp_; }
private:
    void CreateEffect();
    bool CollisionDetection();
private:
    CTrackingProjectileData* data_;
    double castTimestamp_;      // 释放时间
    double lastFrameTimestamp_; // 上一帧时间
    CAbilityEntity* caster_;
    CAbilityEntity* target_;
    CAbility* ability_;
    CVector castPosition_;      // 释放位置
    CVector currentPosition_;   // 当前位置
    CTargetStack* stack_;
};

#endif /* CTrackingProjectile_hpp */
